# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MsgPackSerializerTests bundle.cpp)
target_link_libraries(MsgPackSerializerTests catch)
add_test(MsgPackSerializer MsgPackSerializerTests)
