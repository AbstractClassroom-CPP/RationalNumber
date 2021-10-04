include(FetchContent)
FetchContent_Declare(googletest
	URL https://codeload.github.com/google/googletest/zip/refs/tags/release-1.10.0
	URL_HASH SHA256=94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91
	TIMEOUT 60
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(rational_number_tests RationalNumberTests.cpp)
target_link_libraries(rational_number_tests PRIVATE RationalNumber::RationalNumber gtest_main)

include(GoogleTest)
gtest_discover_tests(rational_number_tests)
