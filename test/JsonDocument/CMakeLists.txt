# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(JsonDocumentTests bundle.cpp)
target_link_libraries(JsonDocumentTests catch)
add_test(JsonDocument JsonDocumentTests)
