#include "RationalNumber.hpp"

RationalNumber::RationalNumber() {
	numerator_ = 0;
	denominator_ = 1;
}

int RationalNumber::getNumerator() const {
	return numerator_;
}

int RationalNumber::getDenominator() const {
	return denominator_;
}
