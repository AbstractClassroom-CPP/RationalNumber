#include "RationalNumber.hpp"
#include <iostream>

int main() {
	RationalNumber fraction(6, 8);
	std::cout << fraction.getNumerator() << "/" << fraction.getDenominator() << "\n";
	return 0;
}
