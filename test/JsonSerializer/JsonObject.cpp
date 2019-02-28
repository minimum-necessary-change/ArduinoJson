// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <string>
#include "utils.hpp"

TEST_CASE("serializeJson(JsonObject)") {
  DynamicJsonDocument doc(4096);
  JsonObject obj = doc.to<JsonObject>();

  SECTION("EmptyObject") {
    checkJson(obj, "{}");
  }

  SECTION("TwoStrings") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";

    checkJson(obj, "{\"key1\":\"value1\",\"key2\":\"value2\"}");
  }

  SECTION("RemoveFirst") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key1");

    checkJson(obj, "{\"key2\":\"value2\"}");
  }

  SECTION("RemoveLast") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key2");

    checkJson(obj, "{\"key1\":\"value1\"}");
  }

  SECTION("RemoveUnexistingKey") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key3");

    checkJson(obj, "{\"key1\":\"value1\",\"key2\":\"value2\"}");
  }

  SECTION("ReplaceExistingKey") {
    obj["key"] = "value1";
    obj["key"] = "value2";

    checkJson(obj, "{\"key\":\"value2\"}");
  }

  SECTION("TwoIntegers") {
    obj["a"] = 1;
    obj["b"] = 2;
    checkJson(obj, "{\"a\":1,\"b\":2}");
  }

  SECTION("serialized(const char*)") {
    obj["a"] = serialized("[1,2]");
    obj["b"] = serialized("[4,5]");
    checkJson(obj, "{\"a\":[1,2],\"b\":[4,5]}");
  }

  SECTION("Two doubles") {
    obj["a"] = 12.34;
    obj["b"] = 56.78;
    checkJson(obj, "{\"a\":12.34,\"b\":56.78}");
  }

  SECTION("TwoNull") {
    obj["a"] = static_cast<char *>(0);
    obj["b"] = static_cast<char *>(0);
    checkJson(obj, "{\"a\":null,\"b\":null}");
  }

  SECTION("TwoBooleans") {
    obj["a"] = true;
    obj["b"] = false;
    checkJson(obj, "{\"a\":true,\"b\":false}");
  }

  SECTION("ThreeNestedArrays") {
    DynamicJsonDocument b(4096);
    DynamicJsonDocument c(4096);

    obj.createNestedArray("a");
    obj["b"] = b.to<JsonArray>();
    obj["c"] = c.to<JsonArray>();

    checkJson(obj, "{\"a\":[],\"b\":[],\"c\":[]}");
  }

  SECTION("ThreeNestedObjects") {
    DynamicJsonDocument b(4096);
    DynamicJsonDocument c(4096);

    obj.createNestedObject("a");
    obj["b"] = b.to<JsonObject>();
    obj["c"] = c.to<JsonObject>();

    checkJson(obj, "{\"a\":{},\"b\":{},\"c\":{}}");
  }
}
