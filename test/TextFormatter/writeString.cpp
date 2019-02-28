// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <catch.hpp>

#include <ArduinoJson/Json/TextFormatter.hpp>
#include <ArduinoJson/Serialization/StaticStringWriter.hpp>

using namespace ARDUINOJSON_NAMESPACE;

void checkString(const char* input, std::string expected) {
  char output[1024];
  StaticStringWriter sb(output, sizeof(output));
  TextFormatter<StaticStringWriter> writer(sb);
  writer.writeString(input);
  REQUIRE(expected == output);
  REQUIRE(writer.bytesWritten() == expected.size());
}

TEST_CASE("TextFormatter::writeString()") {
  SECTION("Null") {
    checkString(0, "null");
  }

  SECTION("EmptyString") {
    checkString("", "\"\"");
  }

  SECTION("QuotationMark") {
    checkString("\"", "\"\\\"\"");
  }

  SECTION("ReverseSolidus") {
    checkString("\\", "\"\\\\\"");
  }

  SECTION("Solidus") {
    checkString("/", "\"/\"");  // but the JSON format allows \/
  }

  SECTION("Backspace") {
    checkString("\b", "\"\\b\"");
  }

  SECTION("Formfeed") {
    checkString("\f", "\"\\f\"");
  }

  SECTION("Newline") {
    checkString("\n", "\"\\n\"");
  }

  SECTION("CarriageReturn") {
    checkString("\r", "\"\\r\"");
  }

  SECTION("HorizontalTab") {
    checkString("\t", "\"\\t\"");
  }
}
