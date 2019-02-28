# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(JsonArrayTests bundle.cpp)
target_link_libraries(JsonArrayTests catch)
add_test(JsonArray JsonArrayTests)
