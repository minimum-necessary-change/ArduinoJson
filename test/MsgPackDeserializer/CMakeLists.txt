# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MsgPackDeserializerTests bundle.cpp)
target_link_libraries(MsgPackDeserializerTests catch)
add_test(MsgPackDeserializer MsgPackDeserializerTests)
