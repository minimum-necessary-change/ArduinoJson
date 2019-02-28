# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(ElementProxyTests bundle.cpp)
target_link_libraries(ElementProxyTests catch)
add_test(ElementProxy ElementProxyTests)
