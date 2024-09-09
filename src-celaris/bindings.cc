#include "includes/bindings.h"

void setBindings(webview::webview &w)
{
    w.bind("count", [&](const std::string &req) -> std::string
           {
               // Imagine that req is properly parsed or use your own JSON parser.
               auto direction = std::stol(req.substr(1, req.size() - 1));
               return "14567"; });
}
