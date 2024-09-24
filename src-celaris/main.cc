#include "includes/celaris.h"

#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#else
int main()
{
#endif

    Celaris c = Celaris();

    // Example of a binding that hooks the frontend greet function
    c.bind("greet", [&](const std::string &req) -> std::string
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

    // Example of scheduled task that posts a string message after 5 seconds
    c.scheduleTask([&c]()
                   {
                       std::cout << "Posting message after 5 seconds" << std::endl;
                       std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
                       std::this_thread::sleep_for(std::chrono::seconds{5});
                       c.postMessage("This is an automated message from C++"); });

    // Example of a scheduled task that posts a JSON object after 10 seconds
    c.scheduleTask([&c]()
                   {
                       std::cout << "Posting JSON after 10 seconds" << std::endl;
                       std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
                       std::this_thread::sleep_for(std::chrono::seconds{10});
                       c.postJson(names); });

    // Example of a scheduled task that posts a JSON object every 15 seconds
    c.scheduleTask([&c]()
                   {
                    //    std::cout << "Posting JSON every 15 seconds" << std::endl;
                    int count = 0;
                    while(true)
                    {
                       json j = {
                           {"origin", "cpp"},
                           {"data", count++},
                           {"type", "count"},
                           {"timestamp", std::chrono::system_clock::now().time_since_epoch().count()},
                           {"message", "This is an automated message from C++"}
                       };
                       std::this_thread::sleep_for(std::chrono::seconds{2});
                       c.postJson(j); 
                   } });

    c.run();
    return 0;
}