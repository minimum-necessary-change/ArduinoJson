// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <stdio.h>
#include <catch.hpp>
#include "utils.hpp"

TEST_CASE("serialize MsgPack object") {
  DynamicJsonDocument doc(4096);
  JsonObject object = doc.to<JsonObject>();

  SECTION("empty") {
    checkObjectSerialization(object, "\x80");
  }

  SECTION("fixmap") {
    object["hello"] = "world";

    checkObjectSerialization(object, "\x81\xA5hello\xA5world");
  }

  SECTION("map 16") {
    for (int i = 0; i < 16; ++i) {
      char key[16];
      sprintf(key, "i%X", i);
      object[key] = i;
    }

    checkObjectSerialization(
        object,
        "\xDE\x00\x10\xA2i0\x00\xA2i1\x01\xA2i2\x02\xA2i3\x03\xA2i4\x04\xA2i5"
        "\x05\xA2i6\x06\xA2i7\x07\xA2i8\x08\xA2i9\x09\xA2iA\x0A\xA2iB\x0B\xA2"
        "iC\x0C\xA2iD\x0D\xA2iE\x0E\xA2iF\x0F");
  }

  // TODO: improve performance and uncomment
  // SECTION("map 32") {
  //   std::string expected("\xDF\x00\x01\x00\x00", 5);
  //
  //   for (int i = 0; i < 65536; ++i) {
  //     char kv[16];
  //     sprintf(kv, "%04x", i);
  //     object[kv] = kv;
  //     expected += '\xA4';
  //     expected += kv;
  //     expected += '\xA4';
  //     expected += kv;
  //   }
  //
  //   checkObjectSerialization(object, expected);
  // }

  SECTION("serialized(const char*)") {
    object["hello"] = serialized("\xDB\x00\x01\x00\x00", 5);
    checkObjectSerialization(object, "\x81\xA5hello\xDB\x00\x01\x00\x00");
  }

  SECTION("serialized(std::string)") {
    object["hello"] = serialized(std::string("\xDB\x00\x01\x00\x00", 5));
    checkObjectSerialization(object, "\x81\xA5hello\xDB\x00\x01\x00\x00");
  }
}
