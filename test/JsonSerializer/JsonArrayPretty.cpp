// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include "utils.hpp"

TEST_CASE("serializeJsonPretty(JsonArray)") {
  DynamicJsonDocument doc(4096);
  JsonArray array = doc.to<JsonArray>();

  SECTION("Empty") {
    checkJsonPretty(array, "[]");
  }

  SECTION("OneElement") {
    array.add(1);

    checkJsonPretty(array,
                    "[\r\n"
                    "  1\r\n"
                    "]");
  }

  SECTION("TwoElements") {
    array.add(1);
    array.add(2);

    checkJsonPretty(array,
                    "[\r\n"
                    "  1,\r\n"
                    "  2\r\n"
                    "]");
  }

  SECTION("EmptyNestedArrays") {
    array.createNestedArray();
    array.createNestedArray();

    checkJsonPretty(array,
                    "[\r\n"
                    "  [],\r\n"
                    "  []\r\n"
                    "]");
  }

  SECTION("NestedArrays") {
    JsonArray nested1 = array.createNestedArray();
    nested1.add(1);
    nested1.add(2);

    JsonObject nested2 = array.createNestedObject();
    nested2["key"] = 3;

    checkJsonPretty(array,
                    "[\r\n"
                    "  [\r\n"
                    "    1,\r\n"
                    "    2\r\n"
                    "  ],\r\n"
                    "  {\r\n"
                    "    \"key\": 3\r\n"
                    "  }\r\n"
                    "]");
  }
}
