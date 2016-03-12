cmake_minimum_required(VERSION 2.8)

project(cppunit)

include(Emplace)

file(STRINGS ${CMAKE_BINARY_DIR}/cppunit_version.txt VERSION)
add_definitions(-DCPPUNIT_VERSION="${VERSION}")

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(src/cppunit)
add_subdirectory(test)

install(
	DIRECTORY include/
	DESTINATION include
	FILES_MATCHING PATTERN "*.h"
)
