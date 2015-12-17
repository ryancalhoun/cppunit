cmake_minimum_required(VERSION 2.8)

project(cppunit)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(src/cppunit)
add_subdirectory(test)

install(DIRECTORY include/ DESTINATION include)
