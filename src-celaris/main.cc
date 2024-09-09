
#include "webview/webview.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "includes/trim.h"
#include "includes/process_path.h"
#include "includes/bindings.h"

namespace fs = std::filesystem;

std::map<std::string, std::string> parseINI(const std::string &filepath, std::map<std::string, std::string> &config)
{
    // std::cout << "Parsing INI file: " << filepath << std::endl;
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

bool checkConfig(const std::map<std::string, std::string> &config)
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

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#else
int main()
{
#endif
    std::map<std::string, std::string> config;
    parseINI(get_executable_path().string() + "/config.ini", config);
    if (!checkConfig(config))
    {
        webview::webview w(false, nullptr);
        w.set_title("Error");
        w.set_size(600, 100, WEBVIEW_HINT_NONE);
        w.set_html("<h3>Error: Invalid Config</h3><p>Visit <a target='_blank' rel='noopener noreferrer' href='https://docs.celaris.io/cpp-config'>https://docs.celaris.io/cpp-config</a> for more information.</p>");
        w.run();
        return 1;
    }

    webview::webview w(true, nullptr);
    w.set_title(config["title"]);
    setBindings(w);
    w.bind("count", [&](const std::string &req) -> std::string
           {
      // Imagine that req is properly parsed or use your own JSON parser.
      auto direction = std::stol(req.substr(1, req.size() - 1));
      return ""; });
    w.set_size(std::stoi(config["width"]), std::stoi(config["height"]), WEBVIEW_HINT_NONE);
    w.navigate(config["url"]);
    w.run();

    return 0;
}