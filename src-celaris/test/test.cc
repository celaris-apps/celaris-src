#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <webview/webview.h>

TEST(JsonTest, BasicStringify)
{
    json j;
    j["name"] = "Celaris";
    j["type"] = "Modern C++ Web Engine for modern desktop apps";

    std::string s = j.dump();

    EXPECT_STREQ(s.c_str(), "{\"name\":\"Celaris\",\"type\":\"Modern C++ Web Engine for modern desktop apps\"}");
}

TEST(JsonTest, BasicParse)
{
    std::string s = "{\"name\":\"Celaris\",\"type\":\"Modern C++ Web Engine for modern desktop apps\"}";
    json j = json::parse(s);

    EXPECT_STREQ(j["name"].get<std::string>().c_str(), "Celaris");
    EXPECT_STREQ(j["type"].get<std::string>().c_str(), "Modern C++ Web Engine for modern desktop apps");
}

TEST(JsonTest, MixedArrayTest)
{
    std::string s = "[\"Celaris\", \"Test\", 265]";
    json j = json::parse(s);

    EXPECT_STREQ(j[0].get<std::string>().c_str(), "Celaris");
    EXPECT_STREQ(j[1].get<std::string>().c_str(), "Test");
    int i = j[2].get<std::int64_t>();
    EXPECT_EQ(i, 265);
}

// TEST(WebViewTest, Basic)
// {
//     webview::webview w(true, nullptr);
//     w.set_title("Error");
//     w.set_size(600, 100, WEBVIEW_HINT_NONE);
//     w.set_html("<h3>Error: Invalid Config</h3><p>Visit <a target='_blank' rel='noopener noreferrer' href='https://docs.celaris.io/cpp-config'>https://docs.celaris.io/cpp-config</a> for more information.</p>");
//     w.run();
// }