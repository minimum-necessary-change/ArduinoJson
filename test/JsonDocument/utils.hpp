// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

static void REQUIRE_JSON(JsonDocument& doc, const std::string& expected) {
  std::string json;
  serializeJson(doc, json);
  REQUIRE(json == expected);
}
