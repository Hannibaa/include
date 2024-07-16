#pragma once
#include <ostream>
#include <numeric>


namespace Math {

	template<typename T>
	struct Quotient {
		T num;
		T don;

		constexpr Quotient(T numerator, T donumerator) {
			auto x = std::gcd(numerator, donumerator);
			num = numerator / x;
			don = donumerator / x;
		}
	};

	template<typename T>
	std::ostream& operator << (std::ostream& os, const Quotient<T>& q) {

		os << "[" << q.num << "|" << q.don << "]";

		return os;

	}

	using q_int = Quotient<int>;

	constexpr q_int operator+(const q_int& d1, const q_int& d2) {

		return q_int(d1.num * d2.don + d1.don * d2.num, d1.don * d2.don);
	}

	constexpr q_int operator*(const  q_int& d1, const q_int& d2) {

		return q_int(d1.num * d2.num, d1.don * d2.don);

	}

	constexpr q_int operator/(const q_int& d1, const q_int& d2) {

		return q_int(d1.num * d2.don, d1.don * d2.num);

	}

}