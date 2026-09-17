# RationalNumber

A simple C++11 rational number library for teaching, using `RationalNumber<int>` or `RationalNumber<ArbitraryInteger>`.
It favors loops and algorithms that are not highly optimized so students can follow the code.

Values reduce after every operation, with positive denominators, zero as `0/1`, and integers as `n/1`.
Access values with `getNumerator()`, `getDenominator()`, `isZero()`, `isInteger()`, and `getDoubleApprox()`.

| Version | Added features |
| --- | --- |
| `v1.0.0` | Reduced fractions, addition, subtraction, and comparisons |
| `v2.0.0` | Multiplication, division, remainder, and unary signs |
| `v3.0.0` | Increment, decrement, and stream operators |
| `v4.0.0` | Templates for `int` or `ArbitraryInteger`, with GoogleTest |
| `v4.0.1` | GitHub Actions unit tests |
| `v5.0.0` | Powers by successive squaring and a backend example |

`power(int)` supports negative exponents by taking the reciprocal, with `power(0)` returning one. Zero to a negative power is invalid.

Zero denominators and division by zero throw `std::domain_error`. Results outside `int` storage throw `std::overflow_error`.
Remainder uses a quotient truncated toward zero. Bitwise operations are not defined for fractions.

Build with CMake 3.14+ and a C++11 compiler

```sh
mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=11
cmake --build .
ctest --output-on-failure
```

Tests use GoogleTest 1.10.0. Tests and examples fetch ArbitraryInteger v3.0.0.
For CMake 4, add `-DCMAKE_POLICY_VERSION_MINIMUM=3.5` when configuring.

Fetch a version with CMake `FetchContent`, link `RationalNumber::RationalNumber`, and include `RationalNumber.hpp`.
Also link `ArbitraryInteger::ArbitraryInteger` when using that backend.
Use `-DBUILD_TESTING=OFF` and `-DRATIONAL_NUMBER_BUILD_EXAMPLE=OFF` for a library-only build.
Stream input accepts an integer or an `n/d` token without internal whitespace.
