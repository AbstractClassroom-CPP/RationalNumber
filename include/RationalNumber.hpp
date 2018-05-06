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
	RationalNumber(int value);
	RationalNumber(const RationalNumber& other);
	RationalNumber& operator=(const RationalNumber& other);
	RationalNumber(int numerator, int denominator);
	bool isZero() const;
	bool isInteger() const;
	double getDoubleApprox() const;
	RationalNumber& operator+=(const RationalNumber& other);
	RationalNumber& operator-=(const RationalNumber& other);
	RationalNumber& operator*=(const RationalNumber& other);

	friend RationalNumber operator+(RationalNumber left, const RationalNumber& right) {
		left += right;
		return left;
	}

	friend RationalNumber operator-(RationalNumber left, const RationalNumber& right) {
		left -= right;
		return left;
	}

	friend bool operator==(const RationalNumber& left, const RationalNumber& right) {
		return left.numerator_ == right.numerator_ && left.denominator_ == right.denominator_;
	}

	friend bool operator!=(const RationalNumber& left, const RationalNumber& right) {
		return !(left == right);
	}

	friend bool operator<(const RationalNumber& left, const RationalNumber& right) {
		return Wide(left.numerator_) * Wide(right.denominator_) < Wide(right.numerator_) * Wide(left.denominator_);
	}

	friend bool operator>(const RationalNumber& left, const RationalNumber& right) {
		return right < left;
	}

	friend bool operator<=(const RationalNumber& left, const RationalNumber& right) {
		return !(right < left);
	}

	friend bool operator>=(const RationalNumber& left, const RationalNumber& right) {
		return !(left < right);
	}

private:

	int numerator_;
	int denominator_;

	static int narrow(Wide value) {
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
			throw std::overflow_error("Rational number does not fit in int");
		}
		return static_cast<int>(value);
	}

	void setValues(Wide n, Wide d) {
		if (d == 0) {
			throw std::domain_error("Denominator cannot be zero");
		}
		if (n == 0) {
			d = 1;
		}
		if (d < 0) {
			n = -n;
			d = -d;
		}
		Wide a = n;
		if (a < 0) {
			a = -a;
		}
		Wide b = d;
		while (b != 0) {
			Wide remainder = a % b;
			a = b;
			b = remainder;
		}
		n /= a;
		d /= a;
		int numerator = narrow(n);
		int denominator = narrow(d);
		numerator_ = numerator;
		denominator_ = denominator;
	}

};

#endif
