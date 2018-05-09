#include "RationalNumber.hpp"
#include <iostream>

int main() {
	RationalNumber fraction(6, 8);
	std::cout << fraction.getNumerator() << "/" << fraction.getDenominator() << "\n";
	RationalNumber scaled = fraction * 4;
	std::cout << scaled.getNumerator() << "/" << scaled.getDenominator() << "\n";
	return 0;
}
