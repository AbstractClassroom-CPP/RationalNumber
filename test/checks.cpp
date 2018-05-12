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
	RationalNumber zero;
	check(zero.getNumerator() == 0);
	check(zero.getDenominator() == 1);
	check(zero.isZero());
	check(zero.isInteger());
	RationalNumber reduced(6, -8);
	check(reduced.getNumerator() == -3);
	check(reduced.getDenominator() == 4);
	check(RationalNumber(0, -12).getDenominator() == 1);
	check(RationalNumber(-12, -3).getNumerator() == 4);
	check(RationalNumber(6, 3).isInteger());
	check(RationalNumber(1, 4).getDoubleApprox() == 0.25);
	bool rejected = false;
	try {
		RationalNumber invalid(1, 0);
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
}

void Addition() {
	check((RationalNumber(1, 6) + RationalNumber(1, 3)).getNumerator() == 1);
	check((RationalNumber(1, 6) + RationalNumber(1, 3)).getDenominator() == 2);
	check((2 + RationalNumber(1, 2)).getNumerator() == 5);
}

void Subtraction() {
	check((RationalNumber(1, 2) - RationalNumber(1, 2)).isZero());
	check((3 - RationalNumber(1, 2)).getNumerator() == 5);
}

void NativeLimits() {
	check(RationalNumber(INT_MIN, INT_MIN) == 1);
	check(RationalNumber(INT_MIN, 2).getNumerator() == INT_MIN / 2);
	check(RationalNumber(0, INT_MIN) == 0);
	check(RationalNumber(INT_MAX, 2) + RationalNumber(INT_MAX, 2) == INT_MAX);
	check(RationalNumber(INT_MIN, 2) + RationalNumber(INT_MIN, 2) == INT_MIN);
}

void Multiplication() {
	check(RationalNumber(2, 3) * RationalNumber(9, 4) == RationalNumber(3, 2));
	check(RationalNumber(1, INT_MAX) * INT_MAX == 1);
}

void Division() {
	check(RationalNumber(2, 3) / RationalNumber(-4, 5) == RationalNumber(-5, 6));
	check(2 / RationalNumber(2, 3) == 3);
}

void Remainder() {
	check(RationalNumber(7, 3) % RationalNumber(2, 3) == RationalNumber(1, 3));
	check(RationalNumber(-7, 3) % RationalNumber(2, 3) == RationalNumber(-1, 3));
	check(RationalNumber(7, 3) % RationalNumber(-2, 3) == RationalNumber(1, 3));
}

void UnarySigns() {
	check(+RationalNumber(-2, 3) == RationalNumber(-2, 3));
	check(-RationalNumber(-2, 3) == RationalNumber(2, 3));
	check(-RationalNumber(0) == 0);
}

void ZeroDivisors() {
	RationalNumber value(3, 4);
	bool rejected = false;
	try {
		value /= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == RationalNumber(3, 4));
	rejected = false;
	try {
		value %= 0;
	}
	catch (const std::domain_error&) {
		rejected = true;
	}
	check(rejected);
	check(value == RationalNumber(3, 4));
}

void Overflow() {
	RationalNumber value(INT_MAX);
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
	RationalNumber value(1, 2);
	check(value++ == RationalNumber(1, 2));
	check(value == RationalNumber(3, 2));
	check(++value == RationalNumber(5, 2));
	check(value-- == RationalNumber(5, 2));
	check(--value == RationalNumber(1, 2));
}

void Streams() {
	std::istringstream in("6/-8 12");
	RationalNumber value;
	in >> value;
	check(value == RationalNumber(-3, 4));
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
	return 0;
}
