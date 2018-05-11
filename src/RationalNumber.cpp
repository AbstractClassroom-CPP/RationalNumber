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

RationalNumber::RationalNumber(int value) {
	numerator_ = value;
	denominator_ = 1;
}

RationalNumber::RationalNumber(const RationalNumber& other) {
	numerator_ = other.numerator_;
	denominator_ = other.denominator_;
}

RationalNumber& RationalNumber::operator=(const RationalNumber& other) {
	numerator_ = other.numerator_;
	denominator_ = other.denominator_;
	return *this;
}

RationalNumber::RationalNumber(int numerator, int denominator) {
	setValues(Wide(numerator), Wide(denominator));
}

bool RationalNumber::isZero() const {
	return numerator_ == 0;
}

bool RationalNumber::isInteger() const {
	return denominator_ == 1;
}

double RationalNumber::getDoubleApprox() const {
	return static_cast<double>(numerator_) / static_cast<double>(denominator_);
}

RationalNumber& RationalNumber::operator+=(const RationalNumber& other) {
	setValues(Wide(numerator_) * Wide(other.denominator_) + Wide(other.numerator_) * Wide(denominator_),
	Wide(denominator_) * Wide(other.denominator_));
	return *this;
}

RationalNumber& RationalNumber::operator-=(const RationalNumber& other) {
	setValues(Wide(numerator_) * Wide(other.denominator_) - Wide(other.numerator_) * Wide(denominator_),
	Wide(denominator_) * Wide(other.denominator_));
	return *this;
}

RationalNumber& RationalNumber::operator*=(const RationalNumber& other) {
	setValues(Wide(numerator_) * Wide(other.numerator_), Wide(denominator_) * Wide(other.denominator_));
	return *this;
}

RationalNumber& RationalNumber::operator/=(const RationalNumber& other) {
	setValues(Wide(numerator_) * Wide(other.denominator_), Wide(denominator_) * Wide(other.numerator_));
	return *this;
}

RationalNumber& RationalNumber::operator%=(const RationalNumber& other) {
	if (other.isZero()) {
		throw std::domain_error("Remainder divisor cannot be zero");
	}
	Wide numerator = (Wide(numerator_) * Wide(other.denominator_)) % (Wide(denominator_) * Wide(other.numerator_));
	setValues(numerator, Wide(denominator_) * Wide(other.denominator_));
	return *this;
}

RationalNumber RationalNumber::operator+() const {
	return *this;
}

RationalNumber RationalNumber::operator-() const {
	RationalNumber result;
	result.setValues(-Wide(numerator_), Wide(denominator_));
	return result;
}

RationalNumber& RationalNumber::operator++() {
	*this += 1;
	return *this;
}

RationalNumber RationalNumber::operator++(int) {
	RationalNumber previous = *this;
	++(*this);
	return previous;
}
