#include "RationalNumber.hpp"
#include <iostream>

int main() {
	RationalNumber<int> a(1, 3);
	RationalNumber<int> b(1, 6);
	std::cout << a << " + " << b << " = " << a + b << "\n";
	std::cout << "product = " << a * b << "\n";
	std::cout << "quotient = " << a / b << "\n";
	std::cout << "approximation = " << a.getDoubleApprox() << "\n";
	return 0;
}
