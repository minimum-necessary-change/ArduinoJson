// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <string>
#include "utils.hpp"

TEST_CASE("serializeJsonPretty(JsonObject)") {
  DynamicJsonDocument doc(4096);
  JsonObject obj = doc.to<JsonObject>();

  SECTION("EmptyObject") {
    checkJsonPretty(obj, "{}");
  }

  SECTION("OneMember") {
    obj["key"] = "value";

    checkJsonPretty(obj,
                    "{\r\n"
                    "  \"key\": \"value\"\r\n"
                    "}");
  }

  SECTION("TwoMembers") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";

    checkJsonPretty(obj,
                    "{\r\n"
                    "  \"key1\": \"value1\",\r\n"
                    "  \"key2\": \"value2\"\r\n"
                    "}");
  }

  SECTION("EmptyNestedContainers") {
    obj.createNestedObject("key1");
    obj.createNestedArray("key2");

    checkJsonPretty(obj,
                    "{\r\n"
                    "  \"key1\": {},\r\n"
                    "  \"key2\": []\r\n"
                    "}");
  }

  SECTION("NestedContainers") {
    JsonObject nested1 = obj.createNestedObject("key1");
    nested1["a"] = 1;

    JsonArray nested2 = obj.createNestedArray("key2");
    nested2.add(2);

    checkJsonPretty(obj,
                    "{\r\n"
                    "  \"key1\": {\r\n"
                    "    \"a\": 1\r\n"
                    "  },\r\n"
                    "  \"key2\": [\r\n"
                    "    2\r\n"
                    "  ]\r\n"
                    "}");
  }
}
