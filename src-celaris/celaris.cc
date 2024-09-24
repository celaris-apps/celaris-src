#include "includes/celaris.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "includes/trim.h"
#include "includes/process_path.h"

namespace fs = std::filesystem;

std::map<std::string, std::string> Celaris::parseINI(const std::string &filepath, std::map<std::string, std::string> &config)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::cerr << "Failed to open config.ini" << std::endl;
        return config;
    }
    std::string line, key, value;

    while (std::getline(file, line))
    {
        std::istringstream is_line(line);
        if (std::getline(is_line, key, '=') && std::getline(is_line, value))
        {
            config[trim(key)] = trim(value);
        }
    }
    return config;
}

bool Celaris::checkConfig(const std::map<std::string, std::string> &config)
{
    if (config.empty())
    {
        std::cerr << "Config file is empty" << std::endl;
        return false;
    }
    if (config.find("title") == config.end())
    {
        std::cerr << "Config file does not contain a title" << std::endl;
        return false;
    }
    if (config.find("width") == config.end())
    {
        std::cerr << "Config file does not contain a width" << std::endl;
        return false;
    }
    if (config.find("height") == config.end())
    {
        std::cerr << "Config file does not contain a height" << std::endl;
        return false;
    }
    if (config.find("url") == config.end())
    {
        std::cerr << "Config file does not contain a url" << std::endl;
        return false;
    }
    return true;
}

Celaris::Celaris() : w(true, nullptr)
{
    parseINI(get_executable_path().string() + "/config.ini", config);
    if (!checkConfig(config))
    {
        w.set_title("Error");
        w.set_size(600, 100, WEBVIEW_HINT_NONE);
        w.set_html("<h3>Error: Invalid Config</h3><p>Visit <a target='_blank' rel='noopener noreferrer' href='https://docs.celaris.cc/guides/cpp-config'>https://docs.celaris.cc/guides/cpp-config</a> for more information.</p>");
        w.run();
    }
    backgroundThread = std::thread(&Celaris::backgroundThreadFunc, this);
}

Celaris::~Celaris()
{
}

void Celaris::run()
{
    // webview::webview w(true, nullptr);
    w.set_title(config["title"]);
    // setBindings(w);
    w.set_size(std::stoi(config["width"]), std::stoi(config["height"]), WEBVIEW_HINT_NONE);
    w.navigate(config["url"]);

    // Leave this here as an example of how to send code from C++ to JS
    // TODO: separate this all out to create a proper event system.
    //  do something every 5 seconds in the background
    // std::thread t([this]()
    //               {
    //     while (true)
    //     {

    //         std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
    //         std::this_thread::sleep_for(std::chrono::seconds {5});
    //         w.dispatch([this, &names]()
    //         {
    //             json j1 = names;
    //             json j2 = {
    //                 {"origin", "cpp"},
    //                 {"data", j1},
    //                 {"type", "names"},
    //                 {"timestamp", std::chrono::system_clock::now().time_since_epoch().count()},
    //                 {"message", "This is an automated message from C++"}
    //             };
    //             std::string js_code = "window.postMessage(" + j2.dump() + ");";
    //             std::cout << "Executing: " << js_code << std::endl;
    //             w.eval(js_code.c_str());
    //         });
    //     } });

    w.run();
}

void Celaris::postMessage(const std::string &data)
{
    std::cout << "Posting message: " << data << std::endl;
    w.dispatch([this, data]()
               {
                   std::string js_code = "window.postMessage(\"" + data + "\");";
                    std::cout << "Executing: " << js_code << std::endl;
                   w.eval(js_code.c_str()); });
}

void Celaris::postJson(const json &data)
{
    std::cout << "Posting message: " << data << std::endl;
    w.dispatch([this, data]()
               {
                   std::string js_code = "window.postMessage(" + data.dump() + ");";
                   std::cout << "Executing: " << js_code << std::endl;
                   w.eval(js_code.c_str()); });
}

void Celaris::setBindings(webview::webview &w)
{
    w.bind("count", [&](const std::string &req) -> std::string
           {
               // Imagine that req is properly parsed or use your own JSON parser.
               auto direction = std::stol(req.substr(1, req.size() - 1));
               return "14567"; });

    w.bind("greet", [&](const std::string &req) -> std::string
           {
               json response;
               auto jsonreq = json::parse(req);
               if (jsonreq.size() != 1)
               {
                   response["message"] = "Invalid request";
               }
               else
               {
                   response["message"] = "Hello " + jsonreq[0].get<std::string>() + ", You have been greeted from C++";
               }
               return response.dump(); });
}

void Celaris::bind(const std::string &name, webview::detail::engine_base::sync_binding_t fn)
{
    w.bind(name, fn);
}

void Celaris::scheduleTask(std::function<void()> task)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.push(task);
    queueCondVar.notify_one();
}

void Celaris::backgroundThreadFunc()
{
    while (!stopBackgroundThread)
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondVar.wait(lock, [this]()
                          { return !taskQueue.empty(); });
        auto task = taskQueue.front();
        taskQueue.pop();
        lock.unlock();
        task();
    }
}
