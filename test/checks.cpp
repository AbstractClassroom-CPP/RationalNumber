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

int main() {
	Normalization();
	Addition();
	return 0;
}
