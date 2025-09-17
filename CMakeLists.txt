cmake_minimum_required(VERSION 3.14)
project(RationalNumber VERSION 4.0.1 LANGUAGES CXX)

add_library(rational_number src/RationalNumber.cpp)
add_library(RationalNumber::RationalNumber ALIAS rational_number)
target_compile_features(rational_number PUBLIC cxx_std_11)
target_include_directories(rational_number PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(rational_number PROPERTIES CXX_EXTENSIONS OFF)

set(rational_number_top_level OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(rational_number_top_level ON)
endif()

if(rational_number_top_level)
	include(CTest)
endif()

option(RATIONAL_NUMBER_BUILD_EXAMPLE "Build the examples" ${rational_number_top_level})

if((rational_number_top_level AND BUILD_TESTING))
	if(NOT TARGET ArbitraryInteger::ArbitraryInteger)
		include(FetchContent)
		FetchContent_Declare(arbitrary_integer
			GIT_REPOSITORY https://github.com/AbstractClassroom-CPP/ArbitraryInteger.git
			GIT_TAG v3.0.0
			GIT_SHALLOW TRUE
		)
		FetchContent_MakeAvailable(arbitrary_integer)
	endif()
endif()

if(RATIONAL_NUMBER_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()

if(rational_number_top_level AND BUILD_TESTING)
	add_subdirectory(test)
endif()
