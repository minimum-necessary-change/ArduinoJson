// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

static void checkArraySerialization(JsonArray array, const char* expected_data,
                                    size_t expected_len) {
  std::string expected(expected_data, expected_data + expected_len);
  std::string actual;
  size_t len = serializeMsgPack(array, actual);
  CAPTURE(array);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

template <size_t N>
static void checkArraySerialization(JsonArray array,
                                    const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  checkArraySerialization(array, expected_data, expected_len);
}

static void checkArraySerialization(JsonArray array,
                                    const std::string& expected) {
  checkArraySerialization(array, expected.data(), expected.length());
}

static void checkObjectSerialization(JsonObject object,
                                     const char* expected_data,
                                     size_t expected_len) {
  std::string expected(expected_data, expected_data + expected_len);
  std::string actual;
  size_t len = serializeMsgPack(object, actual);
  CAPTURE(object);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

template <size_t N>
static void checkObjectSerialization(JsonObject object,
                                     const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  checkObjectSerialization(object, expected_data, expected_len);
}

template <typename T>
static void checkValueSerialization(T value, const char* expected_data,
                                    size_t expected_len) {
  DynamicJsonDocument doc(4096);
  JsonVariant variant = doc.to<JsonVariant>();
  variant.set(value);
  std::string expected(expected_data, expected_data + expected_len);
  std::string actual;
  size_t len = serializeMsgPack(variant, actual);
  CAPTURE(variant);
  REQUIRE(len == expected_len);
  REQUIRE(actual == expected);
}

template <typename T, size_t N>
static void checkValueSerialization(T value, const char (&expected_data)[N]) {
  const size_t expected_len = N - 1;
  checkValueSerialization(value, expected_data, expected_len);
}

template <typename T>
static void checkValueSerialization(T value, const std::string& expected) {
  checkValueSerialization(value, expected.data(), expected.length());
}
