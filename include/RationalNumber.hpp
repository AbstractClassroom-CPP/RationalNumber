#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <cmath>
#include <istream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "RationalNumberStorage.hpp"

template <class T = int>
class RationalNumber {
	typedef typename rational_number_detail::Storage<T>::Wide Wide;

public:
	RationalNumber() {
		numerator_ = 0;
		denominator_ = 1;
	}

	T getNumerator() const {
		return numerator_;
	}

	T getDenominator() const {
		return denominator_;
	}

	template <class Integer>
	RationalNumber(const Integer& value) {
		numerator_ = value;
		denominator_ = 1;
	}

	RationalNumber(const RationalNumber& other) {
		numerator_ = other.numerator_;
		denominator_ = other.denominator_;
	}

	RationalNumber& operator=(const RationalNumber& other) {
		numerator_ = other.numerator_;
		denominator_ = other.denominator_;
		return *this;
	}

	RationalNumber(const T& numerator, const T& denominator) {
		setValues(Wide(numerator), Wide(denominator));
	}

	bool isZero() const {
		return numerator_ == 0;
	}

	bool isInteger() const {
		return denominator_ == 1;
	}

	double getDoubleApprox() const {
		if (isZero()) {
			return 0.0;
		}
		Wide n = numerator_;
		bool negative = n < 0;
		if (negative) {
			n = -n;
		}
		std::size_t numeratorPlaces;
		std::size_t denominatorPlaces;
		double leadingNumerator = leadingDigits(n, numeratorPlaces);
		double leadingDenominator = leadingDigits(Wide(denominator_), denominatorPlaces);
		double result = leadingNumerator / leadingDenominator;
		while (numeratorPlaces > denominatorPlaces && std::isfinite(result)) {
			result *= 10.0;
			numeratorPlaces--;
		}
		while (denominatorPlaces > numeratorPlaces && result != 0.0) {
			result /= 10.0;
			denominatorPlaces--;
		}
		if (negative) {
			result = -result;
		}
		return result;
	}

	RationalNumber& operator+=(const RationalNumber& other) {
		setValues(Wide(numerator_) * Wide(other.denominator_) + Wide(other.numerator_) * Wide(denominator_),
		Wide(denominator_) * Wide(other.denominator_));
		return *this;
	}

	RationalNumber& operator-=(const RationalNumber& other) {
		setValues(Wide(numerator_) * Wide(other.denominator_) - Wide(other.numerator_) * Wide(denominator_),
		Wide(denominator_) * Wide(other.denominator_));
		return *this;
	}

	RationalNumber& operator*=(const RationalNumber& other) {
		setValues(Wide(numerator_) * Wide(other.numerator_), Wide(denominator_) * Wide(other.denominator_));
		return *this;
	}

	RationalNumber& operator/=(const RationalNumber& other) {
		setValues(Wide(numerator_) * Wide(other.denominator_), Wide(denominator_) * Wide(other.numerator_));
		return *this;
	}

	RationalNumber& operator%=(const RationalNumber& other) {
		if (other.isZero()) {
			throw std::domain_error("Remainder divisor cannot be zero");
		}
		Wide numerator = (Wide(numerator_) * Wide(other.denominator_)) % (Wide(denominator_) * Wide(other.numerator_));
		setValues(numerator, Wide(denominator_) * Wide(other.denominator_));
		return *this;
	}

	RationalNumber operator+() const {
		return *this;
	}

	RationalNumber operator-() const {
		RationalNumber result;
		result.setValues(-Wide(numerator_), Wide(denominator_));
		return result;
	}

	RationalNumber& operator++() {
		*this += 1;
		return *this;
	}

	RationalNumber operator++(int) {
		RationalNumber previous = *this;
		++(*this);
		return previous;
	}

	RationalNumber& operator--() {
		*this -= 1;
		return *this;
	}

	RationalNumber operator--(int) {
		RationalNumber previous = *this;
		--(*this);
		return previous;
	}


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

	T numerator_;
	T denominator_;

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
		T numerator = rational_number_detail::Storage<T>::narrow(n);
		T denominator = rational_number_detail::Storage<T>::narrow(d);
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
			if (std::numeric_limits<T>::is_bounded && value < (Wide(std::numeric_limits<T>::min()) + digit) / 10) {
				return false;
			}
			value = value * 10 - digit;
		}
		if (!negative) {
			value = -value;
			if (std::numeric_limits<T>::is_bounded && value > std::numeric_limits<T>::max()) {
				return false;
			}
		}
		return true;
	}

	static double leadingDigits(const Wide& value, std::size_t& skipped) {
		std::ostringstream out;
		out << value;
		std::string text = out.str();
		std::size_t count = text.size();
		if (count > 16) {
			count = 16;
		}
		double result = 0;
		for (std::size_t i = 0; i < count; i++) {
			result = result * 10.0 + (text[i] - '0');
		}
		skipped = text.size() - count;
		return result;
	}

};

#endif
