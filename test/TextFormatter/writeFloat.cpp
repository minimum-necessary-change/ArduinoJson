// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <catch.hpp>
#include <limits>
#include <string>

#include <ArduinoJson/Json/TextFormatter.hpp>
#include <ArduinoJson/Serialization/DynamicStringWriter.hpp>

using namespace ARDUINOJSON_NAMESPACE;

template <typename TFloat>
void checkFloat(TFloat input, const std::string& expected) {
  std::string output;
  DynamicStringWriter<std::string> sb(output);
  TextFormatter<DynamicStringWriter<std::string> > writer(sb);
  writer.writeFloat(input);
  REQUIRE(writer.bytesWritten() == output.size());
  CHECK(expected == output);
}

TEST_CASE("TextFormatter::writeFloat(double)") {
  SECTION("Pi") {
    checkFloat<double>(3.14159265359, "3.141592654");
  }

  SECTION("Signaling NaN") {
    double nan = std::numeric_limits<double>::signaling_NaN();
    checkFloat<double>(nan, "NaN");
  }

  SECTION("Quiet NaN") {
    double nan = std::numeric_limits<double>::quiet_NaN();
    checkFloat<double>(nan, "NaN");
  }

  SECTION("Infinity") {
    double inf = std::numeric_limits<double>::infinity();
    checkFloat<double>(inf, "Infinity");
    checkFloat<double>(-inf, "-Infinity");
  }

  SECTION("Zero") {
    checkFloat<double>(0.0, "0");
    checkFloat<double>(-0.0, "0");
  }

  SECTION("Espilon") {
    checkFloat<double>(2.2250738585072014E-308, "2.225073859e-308");
    checkFloat<double>(-2.2250738585072014E-308, "-2.225073859e-308");
  }

  SECTION("Max double") {
    checkFloat<double>(1.7976931348623157E+308, "1.797693135e308");
    checkFloat<double>(-1.7976931348623157E+308, "-1.797693135e308");
  }

  SECTION("Big exponent") {
    // this test increases coverage of normalize()
    checkFloat<double>(1e255, "1e255");
    checkFloat<double>(1e-255, "1e-255");
  }

  SECTION("Exponentation when <= 1e-5") {
    checkFloat<double>(1e-4, "0.0001");
    checkFloat<double>(1e-5, "1e-5");

    checkFloat<double>(-1e-4, "-0.0001");
    checkFloat<double>(-1e-5, "-1e-5");
  }

  SECTION("Exponentation when >= 1e7") {
    checkFloat<double>(9999999.999, "9999999.999");
    checkFloat<double>(10000000.0, "1e7");

    checkFloat<double>(-9999999.999, "-9999999.999");
    checkFloat<double>(-10000000.0, "-1e7");
  }

  SECTION("Rounding when too many decimals") {
    checkFloat<double>(0.000099999999999, "0.0001");
    checkFloat<double>(0.0000099999999999, "1e-5");
    checkFloat<double>(0.9999999996, "1");
  }

  SECTION("9 decimal places") {
    checkFloat<double>(0.100000001, "0.100000001");
    checkFloat<double>(0.999999999, "0.999999999");

    checkFloat<double>(9.000000001, "9.000000001");
    checkFloat<double>(9.999999999, "9.999999999");
  }

  SECTION("10 decimal places") {
    checkFloat<double>(0.1000000001, "0.1");
    checkFloat<double>(0.9999999999, "1");

    checkFloat<double>(9.0000000001, "9");
    checkFloat<double>(9.9999999999, "10");
  }
}

TEST_CASE("TextFormatter::writeFloat(float)") {
  SECTION("Pi") {
    checkFloat<float>(3.14159265359f, "3.141593");
  }

  SECTION("999.9") {  // issue #543
    checkFloat<float>(999.9f, "999.9");
  }

  SECTION("24.3") {  // # issue #588
    checkFloat<float>(24.3f, "24.3");
  }
}
