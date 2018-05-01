#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <cmath>
#include <istream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

class RationalNumber {
	typedef long long Wide;

public:
	RationalNumber();
	int getNumerator() const;
	int getDenominator() const;

private:

	int numerator_;
	int denominator_;

};

#endif
