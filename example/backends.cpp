#include "RationalNumber.hpp"
#include "ArbitraryInteger.hpp"
#include <iostream>

template <class Integer>
void showFractions() {
	RationalNumber<Integer> a(2, 3);
	RationalNumber<Integer> b(5, 6);
	std::cout << "sum = " << a + b << "\n";
	std::cout << "product = " << a * b << "\n";
	std::cout << "fifth power = " << a.power(5) << "\n";
	std::cout << "reciprocal cube = " << a.power(-3) << "\n";
}

int main() {
	std::cout << "int storage\n";
	showFractions<int>();
	std::cout << "ArbitraryInteger storage\n";
	showFractions<ArbitraryInteger>();
	RationalNumber<ArbitraryInteger> fraction(2, 3);
	std::cout << "fortieth power = " << fraction.power(40) << "\n";
	return 0;
}
