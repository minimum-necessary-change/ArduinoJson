// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <limits>
#include "utils.hpp"

TEST_CASE("serializeJson(JsonVariant)") {
  SECTION("Undefined") {
    checkJson(JsonVariant(), "null");
  }

  SECTION("Null string") {
    checkJson(static_cast<char *>(0), "null");
  }

  SECTION("const char*") {
    checkJson("hello", "\"hello\"");
  }

  SECTION("string") {
    checkJson(std::string("hello"), "\"hello\"");
  }

  SECTION("SerializedValue<const char*>") {
    checkJson(serialized("[1,2]"), "[1,2]");
  }

  SECTION("SerializedValue<std::string>") {
    checkJson(serialized(std::string("[1,2]")), "[1,2]");
  }

  SECTION("Double") {
    checkJson(3.1415927, "3.1415927");
  }

  SECTION("Zero") {
    checkJson(0, "0");
  }

  SECTION("Integer") {
    checkJson(42, "42");
  }

  SECTION("NegativeLong") {
    checkJson(-42, "-42");
  }

  SECTION("UnsignedLong") {
    checkJson(4294967295UL, "4294967295");
  }

  SECTION("True") {
    checkJson(true, "true");
  }

  SECTION("OneFalse") {
    checkJson(false, "false");
  }

#if ARDUINOJSON_USE_LONG_LONG
  SECTION("NegativeInt64") {
    checkJson(-9223372036854775807 - 1, "-9223372036854775808");
  }

  SECTION("PositiveInt64") {
    checkJson(9223372036854775807, "9223372036854775807");
  }

  SECTION("UInt64") {
    checkJson(18446744073709551615U, "18446744073709551615");
  }
#endif
}
