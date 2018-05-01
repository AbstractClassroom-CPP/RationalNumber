cmake_minimum_required(VERSION 3.10)
project(RationalNumber VERSION 1.0.0 LANGUAGES CXX)

add_library(rational_number src/RationalNumber.cpp)
add_library(RationalNumber::RationalNumber ALIAS rational_number)
target_compile_features(rational_number PUBLIC cxx_std_11)
target_include_directories(rational_number PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(rational_number PROPERTIES CXX_EXTENSIONS OFF)

set(rational_number_top_level OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(rational_number_top_level ON)
endif()
