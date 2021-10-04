#ifndef RATIONAL_NUMBER_STORAGE_HPP
#define RATIONAL_NUMBER_STORAGE_HPP

#include <limits>
#include <stdexcept>

namespace rational_number_detail {

template <class T>
struct Storage {
	typedef T Wide;

	static T narrow(const Wide& value) {
		return value;
	}
};

template <>
struct Storage<int> {
	typedef long long Wide;

	static int narrow(Wide value) {
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
			throw std::overflow_error("Rational number does not fit in int");
		}
		return static_cast<int>(value);
	}
};

}

#endif
