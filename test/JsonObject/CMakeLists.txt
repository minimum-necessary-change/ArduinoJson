# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(JsonObjectTests bundle.cpp)
target_link_libraries(JsonObjectTests catch)
add_test(JsonObject JsonObjectTests)
