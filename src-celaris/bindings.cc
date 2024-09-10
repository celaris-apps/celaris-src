#include "includes/bindings.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @brief Set the Bindings object
 *
 * Add your bindings here.
 *
 * @param w
 */
void setBindings(webview::webview &w)
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
                if(jsonreq.size() != 1)
                {
                    response["response"] = "Invalid request";
                }
                else
                {
                    response["response"] = "Hello " + jsonreq[0].get<std::string>() + ", You have been greeted from C++";
                }
                return response.dump(); });
}
