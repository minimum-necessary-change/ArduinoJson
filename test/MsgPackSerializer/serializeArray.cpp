// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include "utils.hpp"

TEST_CASE("serialize MsgPack array") {
  DynamicJsonDocument doc(JSON_ARRAY_SIZE(65536));
  JsonArray array = doc.to<JsonArray>();

  SECTION("empty") {
    checkArraySerialization(array, "\x90");
  }

  SECTION("fixarray") {
    array.add("hello");
    array.add("world");

    checkArraySerialization(array, "\x92\xA5hello\xA5world");
  }

  SECTION("array 16") {
    for (int i = 0; i < 16; i++) array.add(i);

    checkArraySerialization(
        array,
        "\xDC\x00\x10\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D"
        "\x0E\x0F");
  }

  SECTION("array 32") {
    const char* nil = 0;
    for (int i = 0; i < 65536; i++) array.add(nil);

    checkArraySerialization(array, std::string("\xDD\x00\x01\x00\x00", 5) +
                                       std::string(65536, '\xc0'));
  }
}
