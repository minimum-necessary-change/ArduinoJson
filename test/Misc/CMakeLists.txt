# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MiscTests
	bundle.cpp 
	empty.cpp # don't put this one in the bundle
)

target_link_libraries(MiscTests catch)
add_test(Misc MiscTests)
