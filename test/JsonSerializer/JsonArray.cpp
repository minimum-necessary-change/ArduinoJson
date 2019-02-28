// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include "utils.hpp"

TEST_CASE("serializeJson(JsonArray)") {
  StaticJsonDocument<JSON_ARRAY_SIZE(2)> doc;
  JsonArray array = doc.to<JsonArray>();

  SECTION("Empty") {
    checkJson(array, "[]");
  }

  SECTION("Null") {
    array.add(static_cast<char *>(0));

    checkJson(array, "[null]");
  }

  SECTION("OneString") {
    array.add("hello");

    checkJson(array, "[\"hello\"]");
  }

  SECTION("TwoStrings") {
    array.add("hello");
    array.add("world");

    checkJson(array, "[\"hello\",\"world\"]");
  }

  SECTION("OneStringOverCapacity") {
    array.add("hello");
    array.add("world");
    array.add("lost");

    checkJson(array, "[\"hello\",\"world\"]");
  }

  SECTION("One double") {
    array.add(3.1415927);
    checkJson(array, "[3.1415927]");
  }

  SECTION("OneInteger") {
    array.add(1);

    checkJson(array, "[1]");
  }

  SECTION("TwoIntegers") {
    array.add(1);
    array.add(2);

    checkJson(array, "[1,2]");
  }

  SECTION("serialized(const char*)") {
    array.add(serialized("{\"key\":\"value\"}"));

    checkJson(array, "[{\"key\":\"value\"}]");
  }

  SECTION("serialized(char*)") {
    char tmp[] = "{\"key\":\"value\"}";
    array.add(serialized(tmp));

    checkJson(array, "[{\"key\":\"value\"}]");
  }

  SECTION("OneIntegerOverCapacity") {
    array.add(1);
    array.add(2);
    array.add(3);

    checkJson(array, "[1,2]");
  }

  SECTION("OneTrue") {
    array.add(true);

    checkJson(array, "[true]");
  }

  SECTION("OneFalse") {
    array.add(false);

    checkJson(array, "[false]");
  }

  SECTION("TwoBooleans") {
    array.add(false);
    array.add(true);

    checkJson(array, "[false,true]");
  }

  SECTION("OneBooleanOverCapacity") {
    array.add(false);
    array.add(true);
    array.add(false);

    checkJson(array, "[false,true]");
  }

  SECTION("OneEmptyNestedArray") {
    array.createNestedArray();

    checkJson(array, "[[]]");
  }

  SECTION("OneEmptyNestedHash") {
    array.createNestedObject();

    checkJson(array, "[{}]");
  }
}
