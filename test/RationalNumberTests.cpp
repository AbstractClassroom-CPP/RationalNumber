#include "RationalNumber.hpp"
#include <gtest/gtest.h>
#include <climits>
#include <sstream>
#include "ArbitraryInteger.hpp"

TEST(RationalNumberTests, Normalization) {
	RationalNumber<int> zero;
	EXPECT_TRUE(zero.getNumerator() == 0);
	EXPECT_TRUE(zero.getDenominator() == 1);
	EXPECT_TRUE(zero.isZero());
	EXPECT_TRUE(zero.isInteger());
	RationalNumber<int> reduced(6, -8);
	EXPECT_TRUE(reduced.getNumerator() == -3);
	EXPECT_TRUE(reduced.getDenominator() == 4);
	EXPECT_TRUE(RationalNumber<int>(0, -12).getDenominator() == 1);
	EXPECT_TRUE(RationalNumber<int>(-12, -3).getNumerator() == 4);
	EXPECT_TRUE(RationalNumber<int>(6, 3).isInteger());
	EXPECT_TRUE(RationalNumber<int>(1, 4).getDoubleApprox() == 0.25);
	bool rejected = false;
	try {
		RationalNumber<int> invalid(1, 0);
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	EXPECT_TRUE(rejected);
}

TEST(RationalNumberTests, Addition) {
	EXPECT_TRUE((RationalNumber<int>(1, 6) + RationalNumber<int>(1, 3)).getNumerator() == 1);
	EXPECT_TRUE((RationalNumber<int>(1, 6) + RationalNumber<int>(1, 3)).getDenominator() == 2);
	EXPECT_TRUE((2 + RationalNumber<int>(1, 2)).getNumerator() == 5);
}

TEST(RationalNumberTests, Subtraction) {
	EXPECT_TRUE((RationalNumber<int>(1, 2) - RationalNumber<int>(1, 2)).isZero());
	EXPECT_TRUE((3 - RationalNumber<int>(1, 2)).getNumerator() == 5);
}

TEST(RationalNumberTests, NativeLimits) {
	EXPECT_TRUE(RationalNumber<int>(INT_MIN, INT_MIN) == 1);
	EXPECT_TRUE(RationalNumber<int>(INT_MIN, 2).getNumerator() == INT_MIN / 2);
	EXPECT_TRUE(RationalNumber<int>(0, INT_MIN) == 0);
	EXPECT_TRUE(RationalNumber<int>(INT_MAX, 2) + RationalNumber<int>(INT_MAX, 2) == INT_MAX);
	EXPECT_TRUE(RationalNumber<int>(INT_MIN, 2) + RationalNumber<int>(INT_MIN, 2) == INT_MIN);
}

TEST(RationalNumberTests, Multiplication) {
	EXPECT_TRUE(RationalNumber<int>(2, 3) * RationalNumber<int>(9, 4) == RationalNumber<int>(3, 2));
	EXPECT_TRUE(RationalNumber<int>(1, INT_MAX) * INT_MAX == 1);
}

TEST(RationalNumberTests, Division) {
	EXPECT_TRUE(RationalNumber<int>(2, 3) / RationalNumber<int>(-4, 5) == RationalNumber<int>(-5, 6));
	EXPECT_TRUE(2 / RationalNumber<int>(2, 3) == 3);
}

TEST(RationalNumberTests, Remainder) {
	EXPECT_TRUE(RationalNumber<int>(7, 3) % RationalNumber<int>(2, 3) == RationalNumber<int>(1, 3));
	EXPECT_TRUE(RationalNumber<int>(-7, 3) % RationalNumber<int>(2, 3) == RationalNumber<int>(-1, 3));
	EXPECT_TRUE(RationalNumber<int>(7, 3) % RationalNumber<int>(-2, 3) == RationalNumber<int>(1, 3));
}

TEST(RationalNumberTests, UnarySigns) {
	EXPECT_TRUE(+RationalNumber<int>(-2, 3) == RationalNumber<int>(-2, 3));
	EXPECT_TRUE(-RationalNumber<int>(-2, 3) == RationalNumber<int>(2, 3));
	EXPECT_TRUE(-RationalNumber<int>(0) == 0);
}

TEST(RationalNumberTests, ZeroDivisors) {
	RationalNumber<int> value(3, 4);
	bool rejected = false;
	try {
		value /= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	EXPECT_TRUE(rejected);
	EXPECT_TRUE(value == RationalNumber<int>(3, 4));
	rejected = false;
	try {
		value %= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	EXPECT_TRUE(rejected);
	EXPECT_TRUE(value == RationalNumber<int>(3, 4));
}

TEST(RationalNumberTests, Overflow) {
	RationalNumber<int> value(INT_MAX);
	bool rejected = false;
	try {
		value *= 2;
	}
	catch (const std::overflow_error&) {
		rejected = true;
	}
	EXPECT_TRUE(rejected);
	EXPECT_TRUE(value == INT_MAX);
}

TEST(RationalNumberTests, IncrementAndDecrement) {
	RationalNumber<int> value(1, 2);
	EXPECT_TRUE(value++ == RationalNumber<int>(1, 2));
	EXPECT_TRUE(value == RationalNumber<int>(3, 2));
	EXPECT_TRUE(++value == RationalNumber<int>(5, 2));
	EXPECT_TRUE(value-- == RationalNumber<int>(5, 2));
	EXPECT_TRUE(--value == RationalNumber<int>(1, 2));
}

TEST(RationalNumberTests, Streams) {
	std::istringstream in("6/-8 12");
	RationalNumber<int> value;
	in >> value;
	EXPECT_TRUE(value == RationalNumber<int>(-3, 4));
	std::ostringstream out;
	out << value;
	EXPECT_TRUE(out.str() == "-3/4");
	in >> value;
	EXPECT_TRUE(value == 12);
	std::istringstream invalid("1/0");
	invalid >> value;
	EXPECT_TRUE(invalid.fail());
	EXPECT_TRUE(value == 12);
}

TEST(RationalNumberTests, NativeAssignment) {
	RationalNumber<int> value(2, 3);
	value = -7;
	EXPECT_TRUE(value.getNumerator() == -7);
	EXPECT_TRUE(value.getDenominator() == 1);
	RationalNumber<int> copy(value);
	EXPECT_TRUE(copy == value);
	RationalNumber<int>& same = value;
	value = same;
	EXPECT_TRUE(value == -7);
}

TEST(RationalNumberTests, Aliasing) {
	RationalNumber<int> value(2, 3);
	value += value;
	EXPECT_TRUE(value == RationalNumber<int>(4, 3));
	value *= value;
	EXPECT_TRUE(value == RationalNumber<int>(16, 9));
	value /= value;
	EXPECT_TRUE(value == 1);
	value -= value;
	EXPECT_TRUE(value == 0);
}

TEST(RationalNumberTests, Comparison) {
	EXPECT_TRUE(RationalNumber<int>(2, 4) == RationalNumber<int>(1, 2));
	EXPECT_TRUE(RationalNumber<int>(-1, 3) < RationalNumber<int>(-1, 4));
	EXPECT_TRUE(RationalNumber<int>(INT_MAX, INT_MAX - 1) > RationalNumber<int>(INT_MAX - 1, INT_MAX));
	EXPECT_TRUE(RationalNumber<int>(INT_MIN, INT_MAX) < -1);
	EXPECT_TRUE(0 <= RationalNumber<int>(0));
	EXPECT_TRUE(2 >= RationalNumber<int>(2));
	EXPECT_TRUE(RationalNumber<int>(1, 2) != 1);
}

TEST(RationalNumberTests, FailedAddition) {
	RationalNumber<int> value(INT_MAX);
	bool rejected = false;
	try {
		value += 1;
	}
	catch (const std::overflow_error&) {
		rejected = true;
	}
	EXPECT_TRUE(rejected);
	EXPECT_TRUE(value == INT_MAX);
}

TEST(RationalNumberTests, InvalidDenominators) {
	EXPECT_THROW(RationalNumber<int>(0, 0), std::domain_error);
	EXPECT_THROW(RationalNumber<int>(1, INT_MIN), std::overflow_error);
	EXPECT_THROW(RationalNumber<int>(INT_MIN, -1), std::overflow_error);
	EXPECT_EQ(RationalNumber<int>(2, INT_MIN), RationalNumber<int>(-1, 1073741824));
}

TEST(RationalNumberTests, CheckedArithmetic) {
	EXPECT_THROW(-RationalNumber<int>(INT_MIN), std::overflow_error);
	EXPECT_THROW(RationalNumber<int>(INT_MIN) / -1, std::overflow_error);
	EXPECT_THROW(RationalNumber<int>(1, INT_MAX) * RationalNumber<int>(1, 2), std::overflow_error);
	EXPECT_EQ(RationalNumber<int>(INT_MIN) % -1, RationalNumber<int>(0));
	EXPECT_EQ(RationalNumber<int>(INT_MIN, INT_MAX) - RationalNumber<int>(INT_MIN, INT_MAX), RationalNumber<int>(0));
}

TEST(RationalNumberTests, MalformedStreams) {
	const char* tokens[] = {"", "+", "-", "1/", "/2", "1/2/3", "abc", "1/0", "2147483648", "-2147483649"};
	for (unsigned int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
		std::istringstream in(tokens[i]);
		RationalNumber<int> value(3, 4);
		in >> value;
		EXPECT_TRUE(in.fail()) << tokens[i];
		EXPECT_EQ(value, RationalNumber<int>(3, 4));
	}
}

TEST(RationalNumberTests, BigArithmetic) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	ArbitraryInteger large("1234567890123456789012345678901234567890");
	Fraction a(large, 3);
	Fraction b(7, 5);
	EXPECT_EQ((a + b) - b, a);
	EXPECT_EQ((a * b) / b, a);
	EXPECT_EQ(a.getNumerator(), large / 3);
	EXPECT_EQ(a.getDenominator(), ArbitraryInteger(1));
	EXPECT_EQ(Fraction(large, large * 7), Fraction(1, 7));
	EXPECT_EQ(Fraction(0, -large), Fraction(0));
}

TEST(RationalNumberTests, BigApproximation) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	ArbitraryInteger large("1" + std::string(400, '0'));
	Fraction close(large + 1, large - 1);
	EXPECT_NEAR(close.getDoubleApprox(), 1.0, 1e-14);
	EXPECT_NEAR(Fraction(-large, large * 3 + 1).getDoubleApprox(), -1.0 / 3.0, 1e-14);
	EXPECT_TRUE(std::isinf(Fraction(large).getDoubleApprox()));
	EXPECT_EQ(Fraction(1, large).getDoubleApprox(), 0.0);
	EXPECT_EQ(Fraction(0).getDoubleApprox(), 0.0);
}

TEST(RationalNumberTests, BigMixedIntegers) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	Fraction value = 2;
	value = 3;
	EXPECT_EQ(2 + value, Fraction(5));
	EXPECT_EQ(value + 2, Fraction(5));
	EXPECT_EQ(ArbitraryInteger(5) - value, Fraction(2));
	EXPECT_EQ(value * 2, Fraction(6));
	EXPECT_EQ(2 / value, Fraction(2, 3));
	EXPECT_EQ(value % 2, Fraction(1));
	EXPECT_TRUE(2 < value);
	EXPECT_TRUE(value > ArbitraryInteger(2));
	value += 2;
	value -= 1;
	value *= 3;
	value /= 2;
	value %= 4;
	EXPECT_EQ(value, Fraction(2));
	EXPECT_EQ(value++, Fraction(2));
	EXPECT_EQ(--value, Fraction(2));
}

TEST(RationalNumberTests, BigStreams) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	std::istringstream in("123456789012345678901234567890/7");
	Fraction value;
	in >> value;
	EXPECT_FALSE(in.fail());
	EXPECT_EQ(value, Fraction(ArbitraryInteger("123456789012345678901234567890"), 7));
	std::ostringstream out;
	out << value;
	std::istringstream again(out.str());
	Fraction copy;
	again >> copy;
	EXPECT_EQ(copy, value);
}

TEST(RationalNumberTests, BigZeroDivisors) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	Fraction value(7, 9);
	EXPECT_THROW(value /= 0, std::domain_error);
	EXPECT_THROW(value %= 0, std::domain_error);
	EXPECT_EQ(value, Fraction(7, 9));
	EXPECT_THROW(Fraction(1, 0), std::domain_error);
}

TEST(RationalNumberTests, Powers) {
	const RationalNumber<int> value(2, 3);
	EXPECT_EQ(value.power(0), RationalNumber<int>(1));
	EXPECT_EQ(value.power(5), RationalNumber<int>(32, 243));
	EXPECT_EQ(value.power(-3), RationalNumber<int>(27, 8));
	EXPECT_EQ(value, RationalNumber<int>(2, 3));
	EXPECT_EQ(RationalNumber<int>(-2, 3).power(3), RationalNumber<int>(-8, 27));
	EXPECT_EQ(RationalNumber<int>(-2, 3).power(4), RationalNumber<int>(16, 81));
	EXPECT_EQ(RationalNumber<int>(0).power(0), RationalNumber<int>(1));
	EXPECT_EQ(RationalNumber<int>(0).power(9), RationalNumber<int>(0));
	EXPECT_THROW(RationalNumber<int>(0).power(-1), std::domain_error);
}

TEST(RationalNumberTests, PowerLimits) {
	EXPECT_EQ(RationalNumber<int>(-1).power(INT_MIN), RationalNumber<int>(1));
	EXPECT_EQ(RationalNumber<int>(-1).power(INT_MAX), RationalNumber<int>(-1));
	EXPECT_EQ(RationalNumber<int>(1).power(INT_MIN), RationalNumber<int>(1));
	EXPECT_EQ(RationalNumber<int>(INT_MAX).power(1), RationalNumber<int>(INT_MAX));
	EXPECT_EQ(RationalNumber<int>(-2).power(31), RationalNumber<int>(INT_MIN));
	EXPECT_THROW(RationalNumber<int>(2).power(31), std::overflow_error);
	EXPECT_THROW(RationalNumber<int>(1, 2).power(31), std::overflow_error);
}

TEST(RationalNumberTests, BigPowers) {
	typedef RationalNumber<ArbitraryInteger> Fraction;
	Fraction value(2, 3);
	EXPECT_EQ(value.power(40), Fraction(ArbitraryInteger("1099511627776"), ArbitraryInteger("12157665459056928801")));
	EXPECT_EQ(value.power(-40) * value.power(40), Fraction(1));
	EXPECT_EQ(Fraction(-1).power(INT_MIN), Fraction(1));
	EXPECT_THROW(Fraction(0).power(-1), std::domain_error);
	EXPECT_EQ(Fraction(0).power(0), Fraction(1));
}

