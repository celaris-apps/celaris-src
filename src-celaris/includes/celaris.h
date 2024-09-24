#pragma once

#include <webview/webview.h>
#include <thread>
#include <queue>
#include <mutex>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Celaris
{
public:
    Celaris();
    ~Celaris();
    void createWindow();
    void run();
    void postMessage(const std::string &data);
    void postJson(const json &data);
    void setBindings(webview::webview &w);
    void bind(const std::string &name, webview::detail::engine_base::sync_binding_t fn);
    void scheduleTask(std::function<void()> task);

private:
    std::map<std::string, std::string> parseINI(const std::string &filepath, std::map<std::string, std::string> &config);
    bool checkConfig(const std::map<std::string, std::string> &config);
    void backgroundThreadFunc();

    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondVar;
    std::thread backgroundThread;
    bool stopBackgroundThread = false;
    std::map<std::string, std::string> config;
    webview::webview w;
};