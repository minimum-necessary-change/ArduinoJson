// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("serialize MsgPack value") {
  SECTION("undefined") {
    checkValueSerialization(JsonVariant(),
                            "\xC0");  // we represent undefined as nil
  }

  SECTION("nil") {
    const char* nil = 0;  // ArduinoJson uses a string for null
    checkValueSerialization(nil, "\xC0");
  }

  SECTION("bool") {
    checkValueSerialization(false, "\xC2");
    checkValueSerialization(true, "\xC3");
  }

  SECTION("positive fixint") {
    checkValueSerialization(0, "\x00");
    checkValueSerialization(127, "\x7F");
  }

  SECTION("uint 8") {
    checkValueSerialization(128, "\xCC\x80");
    checkValueSerialization(255, "\xCC\xFF");
  }

  SECTION("uint 16") {
    checkValueSerialization(256, "\xCD\x01\x00");
    checkValueSerialization(0xFFFF, "\xCD\xFF\xFF");
  }

  SECTION("uint 32") {
    checkValueSerialization(0x00010000U, "\xCE\x00\x01\x00\x00");
    checkValueSerialization(0x12345678U, "\xCE\x12\x34\x56\x78");
    checkValueSerialization(0xFFFFFFFFU, "\xCE\xFF\xFF\xFF\xFF");
  }

#if ARDUINOJSON_USE_LONG_LONG
  SECTION("uint 64") {
    checkValueSerialization(0x0001000000000000U,
                            "\xCF\x00\x01\x00\x00\x00\x00\x00\x00");
    checkValueSerialization(0x123456789ABCDEF0U,
                            "\xCF\x12\x34\x56\x78\x9A\xBC\xDE\xF0");
    checkValueSerialization(0xFFFFFFFFFFFFFFFFU,
                            "\xCF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF");
  }
#endif

  SECTION("negative fixint") {
    checkValueSerialization(-1, "\xFF");
    checkValueSerialization(-32, "\xE0");
  }

  SECTION("int 8") {
    checkValueSerialization(-33, "\xD0\xDF");
    checkValueSerialization(-128, "\xD0\x80");
  }

  SECTION("int 16") {
    checkValueSerialization(-129, "\xD1\xFF\x7F");
    checkValueSerialization(-32768, "\xD1\x80\x00");
  }

  SECTION("int 32") {
    checkValueSerialization(-32769, "\xD2\xFF\xFF\x7F\xFF");
    checkValueSerialization(-2147483647 - 1, "\xD2\x80\x00\x00\x00");
  }

#if ARDUINOJSON_USE_LONG_LONG
  SECTION("int 64") {
    checkValueSerialization(int64_t(0xFEDCBA9876543210),
                            "\xD3\xFE\xDC\xBA\x98\x76\x54\x32\x10");
  }
#endif

  SECTION("float 32") {
    checkValueSerialization(1.25, "\xCA\x3F\xA0\x00\x00");
  }

  SECTION("float 64") {
    checkValueSerialization(3.1415, "\xCB\x40\x09\x21\xCA\xC0\x83\x12\x6F");
  }

  SECTION("fixstr") {
    checkValueSerialization("", "\xA0");
    checkValueSerialization("hello world hello world hello !",
                            "\xBFhello world hello world hello !");
  }

  SECTION("str 8") {
    checkValueSerialization("hello world hello world hello !!",
                            "\xD9\x20hello world hello world hello !!");
  }

  SECTION("str 16") {
    std::string shortest(256, '?');
    checkValueSerialization(shortest.c_str(),
                            std::string("\xDA\x01\x00", 3) + shortest);

    std::string longest(65535, '?');
    checkValueSerialization(longest.c_str(),
                            std::string("\xDA\xFF\xFF", 3) + longest);
  }

  SECTION("str 32") {
    std::string shortest(65536, '?');
    checkValueSerialization(shortest.c_str(),
                            std::string("\xDB\x00\x01\x00\x00", 5) + shortest);
  }

  SECTION("serialized(const char*)") {
    checkValueSerialization(serialized("\xDA\xFF\xFF"), "\xDA\xFF\xFF");
    checkValueSerialization(serialized("\xDB\x00\x01\x00\x00", 5),
                            "\xDB\x00\x01\x00\x00");
  }
}
