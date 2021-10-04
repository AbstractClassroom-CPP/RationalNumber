#include "RationalNumber.hpp"
#include <climits>
#include <sstream>
#include <stdexcept>

void check(bool condition) {
	if (!condition) {
		throw std::runtime_error("Fraction check failed");
	}
}

void Normalization() {
	RationalNumber<int> zero;
	check(zero.getNumerator() == 0);
	check(zero.getDenominator() == 1);
	check(zero.isZero());
	check(zero.isInteger());
	RationalNumber<int> reduced(6, -8);
	check(reduced.getNumerator() == -3);
	check(reduced.getDenominator() == 4);
	check(RationalNumber<int>(0, -12).getDenominator() == 1);
	check(RationalNumber<int>(-12, -3).getNumerator() == 4);
	check(RationalNumber<int>(6, 3).isInteger());
	check(RationalNumber<int>(1, 4).getDoubleApprox() == 0.25);
	bool rejected = false;
	try {
		RationalNumber<int> invalid(1, 0);
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
}

void Addition() {
	check((RationalNumber<int>(1, 6) + RationalNumber<int>(1, 3)).getNumerator() == 1);
	check((RationalNumber<int>(1, 6) + RationalNumber<int>(1, 3)).getDenominator() == 2);
	check((2 + RationalNumber<int>(1, 2)).getNumerator() == 5);
}

void Subtraction() {
	check((RationalNumber<int>(1, 2) - RationalNumber<int>(1, 2)).isZero());
	check((3 - RationalNumber<int>(1, 2)).getNumerator() == 5);
}

void NativeLimits() {
	check(RationalNumber<int>(INT_MIN, INT_MIN) == 1);
	check(RationalNumber<int>(INT_MIN, 2).getNumerator() == INT_MIN / 2);
	check(RationalNumber<int>(0, INT_MIN) == 0);
	check(RationalNumber<int>(INT_MAX, 2) + RationalNumber<int>(INT_MAX, 2) == INT_MAX);
	check(RationalNumber<int>(INT_MIN, 2) + RationalNumber<int>(INT_MIN, 2) == INT_MIN);
}

void Multiplication() {
	check(RationalNumber<int>(2, 3) * RationalNumber<int>(9, 4) == RationalNumber<int>(3, 2));
	check(RationalNumber<int>(1, INT_MAX) * INT_MAX == 1);
}

void Division() {
	check(RationalNumber<int>(2, 3) / RationalNumber<int>(-4, 5) == RationalNumber<int>(-5, 6));
	check(2 / RationalNumber<int>(2, 3) == 3);
}

void Remainder() {
	check(RationalNumber<int>(7, 3) % RationalNumber<int>(2, 3) == RationalNumber<int>(1, 3));
	check(RationalNumber<int>(-7, 3) % RationalNumber<int>(2, 3) == RationalNumber<int>(-1, 3));
	check(RationalNumber<int>(7, 3) % RationalNumber<int>(-2, 3) == RationalNumber<int>(1, 3));
}

void UnarySigns() {
	check(+RationalNumber<int>(-2, 3) == RationalNumber<int>(-2, 3));
	check(-RationalNumber<int>(-2, 3) == RationalNumber<int>(2, 3));
	check(-RationalNumber<int>(0) == 0);
}

void ZeroDivisors() {
	RationalNumber<int> value(3, 4);
	bool rejected = false;
	try {
		value /= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == RationalNumber<int>(3, 4));
	rejected = false;
	try {
		value %= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == RationalNumber<int>(3, 4));
}

void Overflow() {
	RationalNumber<int> value(INT_MAX);
	bool rejected = false;
	try {
		value *= 2;
	}
	catch (const std::overflow_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == INT_MAX);
}

void IncrementAndDecrement() {
	RationalNumber<int> value(1, 2);
	check(value++ == RationalNumber<int>(1, 2));
	check(value == RationalNumber<int>(3, 2));
	check(++value == RationalNumber<int>(5, 2));
	check(value-- == RationalNumber<int>(5, 2));
	check(--value == RationalNumber<int>(1, 2));
}

void Streams() {
	std::istringstream in("6/-8 12");
	RationalNumber<int> value;
	in >> value;
	check(value == RationalNumber<int>(-3, 4));
	std::ostringstream out;
	out << value;
	check(out.str() == "-3/4");
	in >> value;
	check(value == 12);
	std::istringstream invalid("1/0");
	invalid >> value;
	check(invalid.fail());
	check(value == 12);
}

void NativeAssignment() {
	RationalNumber<int> value(2, 3);
	value = -7;
	check(value.getNumerator() == -7);
	check(value.getDenominator() == 1);
	RationalNumber<int> copy(value);
	check(copy == value);
	RationalNumber<int>& same = value;
	value = same;
	check(value == -7);
}

void Aliasing() {
	RationalNumber<int> value(2, 3);
	value += value;
	check(value == RationalNumber<int>(4, 3));
	value *= value;
	check(value == RationalNumber<int>(16, 9));
	value /= value;
	check(value == 1);
	value -= value;
	check(value == 0);
}

void Comparison() {
	check(RationalNumber<int>(2, 4) == RationalNumber<int>(1, 2));
	check(RationalNumber<int>(-1, 3) < RationalNumber<int>(-1, 4));
	check(RationalNumber<int>(INT_MAX, INT_MAX - 1) > RationalNumber<int>(INT_MAX - 1, INT_MAX));
	check(RationalNumber<int>(INT_MIN, INT_MAX) < -1);
	check(0 <= RationalNumber<int>(0));
	check(2 >= RationalNumber<int>(2));
	check(RationalNumber<int>(1, 2) != 1);
}

void FailedAddition() {
	RationalNumber<int> value(INT_MAX);
	bool rejected = false;
	try {
		value += 1;
	}
	catch (const std::overflow_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == INT_MAX);
}

int main() {
	Normalization();
	Addition();
	Subtraction();
	NativeLimits();
	Multiplication();
	Division();
	Remainder();
	UnarySigns();
	ZeroDivisors();
	Overflow();
	IncrementAndDecrement();
	Streams();
	NativeAssignment();
	Aliasing();
	Comparison();
	FailedAddition();
	return 0;
}
