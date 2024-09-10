#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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