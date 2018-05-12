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
	RationalNumber& operator/=(const RationalNumber& other);
	RationalNumber& operator%=(const RationalNumber& other);
	RationalNumber operator+() const;
	RationalNumber operator-() const;
	RationalNumber& operator++();
	RationalNumber operator++(int);
	RationalNumber& operator--();
	RationalNumber operator--(int);

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

	friend RationalNumber operator*(RationalNumber left, const RationalNumber& right) {
		left *= right;
		return left;
	}

	friend RationalNumber operator/(RationalNumber left, const RationalNumber& right) {
		left /= right;
		return left;
	}

	friend RationalNumber operator%(RationalNumber left, const RationalNumber& right) {
		left %= right;
		return left;
	}

	friend std::ostream& operator<<(std::ostream& out, const RationalNumber& value) {
		out << value.numerator_ << "/" << value.denominator_;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, RationalNumber& value) {
		std::string text;
		if (!(in >> text)) {
			return in;
		}
		std::size_t slash = text.find('/');
		Wide numerator;
		Wide denominator = 1;
		bool valid = false;
		if (slash == std::string::npos) {
			valid = readInteger(text, numerator);
		}
		else {
			valid = readInteger(text.substr(0, slash), numerator) && readInteger(text.substr(slash + 1), denominator);
		}
		if (!valid) {
			in.setstate(std::ios::failbit);
			return in;
		}
		try {
			value.setValues(numerator, denominator);
		}
		catch (const std::domain_error&) {
			in.setstate(std::ios::failbit);
		}
		catch (const std::overflow_error&) {
			in.setstate(std::ios::failbit);
		}
		return in;
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

	static bool readInteger(const std::string& text, Wide& value) {
		if (text.empty()) {
			return false;
		}
		std::size_t i = 0;
		bool negative = false;
		if (text[i] == '-' || text[i] == '+') {
			negative = text[i] == '-';
			i++;
		}
		if (i == text.size()) {
			return false;
		}
		value = 0;
		for (; i < text.size(); i++) {
			if (text[i] < '0' || text[i] > '9') {
				return false;
			}
			int digit = text[i] - '0';
			if (value < (Wide(std::numeric_limits<int>::min()) + digit) / 10) {
				return false;
			}
			value = value * 10 - digit;
		}
		if (!negative) {
			value = -value;
			if (value > std::numeric_limits<int>::max()) {
				return false;
			}
		}
		return true;
	}

};

#endif
