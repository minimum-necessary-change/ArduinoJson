# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(JsonVariantTests bundle.cpp)
target_link_libraries(JsonVariantTests catch)
add_test(JsonVariant JsonVariantTests)
