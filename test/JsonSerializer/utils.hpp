// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

static void checkJson(JsonArray array, std::string expected) {
  std::string actual;
  size_t actualLen = serializeJson(array, actual);
  REQUIRE(expected == actual);
  REQUIRE(actualLen == expected.size());
  size_t measuredLen = measureJson(array);
  REQUIRE(measuredLen == expected.size());
}

static void checkJsonPretty(JsonArray array, std::string expected) {
  std::string actual;
  size_t actualLen = serializeJsonPretty(array, actual);
  size_t measuredLen = measureJsonPretty(array);
  CHECK(actualLen == expected.size());
  CHECK(measuredLen == expected.size());
  REQUIRE(expected == actual);
}

static void checkJson(const JsonObject obj, const std::string &expected) {
  char actual[256];
  size_t actualLen = serializeJson(obj, actual);
  size_t measuredLen = measureJson(obj);

  REQUIRE(expected == actual);
  REQUIRE(expected.size() == actualLen);
  REQUIRE(expected.size() == measuredLen);
}

static void checkJsonPretty(const JsonObject obj, const std::string expected) {
  char json[256];

  size_t actualLen = serializeJsonPretty(obj, json);
  size_t measuredLen = measureJsonPretty(obj);

  REQUIRE(json == expected);
  REQUIRE(expected.size() == actualLen);
  REQUIRE(expected.size() == measuredLen);
}

template <typename T>
static void checkJson(T value, const std::string &expected) {
  DynamicJsonDocument doc(4096);
  doc.to<JsonVariant>().set(value);
  char buffer[256] = "";
  size_t returnValue = serializeJson(doc, buffer, sizeof(buffer));
  REQUIRE(expected == buffer);
  REQUIRE(expected.size() == returnValue);
}
