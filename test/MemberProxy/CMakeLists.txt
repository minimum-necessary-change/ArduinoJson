# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MemberProxyTests bundle.cpp)
target_link_libraries(MemberProxyTests catch)
add_test(MemberProxy MemberProxyTests)
