project(cppunit_test)

set(SOURCES
	cppunit_test.cpp
)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_executable(cppunit_test ${SOURCES})
add_test(cppunit_test cppunit_test)

target_link_libraries(cppunit_test
	cppunit
)


