cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(georithm)

add_library(georithm INTERFACE)
target_include_directories(
	georithm
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
	georithm
	INTERFACE
	cxx_std_20
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)

	add_executable(
		test_georithm
		${CMAKE_CURRENT_SOURCE_DIR}/test/LineTest.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/test/RectTest.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/test/VectorTest.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
	)

	target_link_libraries(
		test_georithm
		PRIVATE
		georithm
	)

	enable_testing()
	add_test(
		NAME GeorithmTestSuite
		COMMAND test_georithm
	)
endif()
