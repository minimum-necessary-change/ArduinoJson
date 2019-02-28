# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(JsonSerializerTests bundle.cpp)
target_link_libraries(JsonSerializerTests catch)
add_test(JsonSerializer JsonSerializerTests)
