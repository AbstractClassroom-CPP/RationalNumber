# RationalNumber

A simple C++11 rational number library for teaching, using `RationalNumber` with `int` storage.
It favors loops and algorithms that are not highly optimized so students can follow the code.

Values reduce after every operation, with positive denominators, zero as `0/1`, and integers as `n/1`.
Access values with `getNumerator()`, `getDenominator()`, `isZero()`, `isInteger()`, and `getDoubleApprox()`.

| Version | Added features |
| --- | --- |
| `v1.0.0` | Reduced fractions, addition, subtraction, and comparisons |
| `v2.0.0` | Multiplication, division, remainder, and unary signs |

Zero denominators and division by zero throw `std::domain_error`. Results outside `int` storage throw `std::overflow_error`.
Remainder uses a quotient truncated toward zero. Bitwise operations are not defined for fractions.

Build with CMake 3.10+ and a C++11 compiler

```sh
mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=11
cmake --build .
ctest --output-on-failure
```

Link `RationalNumber::RationalNumber` and include `RationalNumber.hpp`.
Use `-DBUILD_TESTING=OFF` or `-DRATIONAL_NUMBER_BUILD_EXAMPLE=OFF` to disable those builds.
