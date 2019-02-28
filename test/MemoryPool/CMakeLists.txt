# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MemoryPoolTests bundle.cpp)
target_link_libraries(MemoryPoolTests catch)
add_test(MemoryPool MemoryPoolTests)
