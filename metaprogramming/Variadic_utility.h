#pragma once
#include <type_traits>
#include <cstdarg>

///////////////////////////////////////////////////////////
//   Add Mult Max and Min in Variadic function
///////////////////////////////////////////////////////////

template<typename TT>
constexpr TT add(const size_t n...) {

	static_assert(std::is_arithmetic<TT>::value, "Type Should be Arithmetic type");
	using T = typename std::conditional<std::is_floating_point<TT>::value, double, TT>::type;

	T Sum{};
	std::va_list args;
	va_start(args, n);

	for (size_t i = n; i--;) {
		Sum += va_arg(args, T);
	}

	va_end(args);

	return TT(Sum);
}

template<typename TT>
TT mult(size_t n...) {

	static_assert(std::is_arithmetic<TT>::value, "Type Should be Arithmetic type");
	using T = typename std::conditional<std::is_floating_point<TT>::value, double, TT>::type;

	T Prod{T(1)};
	std::va_list args;
	va_start(args, n);

	for (size_t i = n; i--;) {
		Prod *= va_arg(args, T);
	}

	va_end(args);

	return TT(Prod);
}

template<typename TT>
TT Max(size_t n...) {

	static_assert(std::is_arithmetic<TT>::value, "Type Should be Arithmetic type");
	using T = typename std::conditional<std::is_floating_point<TT>::value, double, TT>::type;

	std::va_list args;
	va_start(args, n);
	T max{va_arg(args, T)};

	for (size_t i = n - 1; i--;)
	{
		T a = va_arg(args, T);
		max = max > a ? max : a;
	}

	va_end(args);

	return TT(max);
}

template<typename TT>
TT Min(size_t n...) {

	static_assert(std::is_arithmetic<TT>::value, "Type Should be Arithmetic type");
	using T = typename std::conditional<std::is_floating_point<TT>::value, double, TT>::type;

	std::va_list args;
	va_start(args, n);
	T min{va_arg(args, T)};

	for (size_t i = n - 1; i--;)
	{
		T a = va_arg(args, T);
		min = min < a ? min : a;
	}

	va_end(args);

	return TT(min);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                                     VARIADIC TEMPLATE 
///////////////////////////////////////////////////////////////////////////////////////////////

// get number of argument
template<typename T>
int get_number_args(const T& t) {
	return 1;
}

template<typename T0, typename ...T>
int get_number_args(const T0& t0, const T&...t) {
	return 1 + get_number_args(t...);
}

template<typename ...TN>
size_t get_number_args_() {
	return sizeof...(TN);
}

template<typename T>
constexpr T add_() { return T{}; }

template<typename T,T N0, T...N>
constexpr T add_() {
	 T x{N0};
	x += add_<T, N...>();
	return x;
}

template<typename T>
constexpr T mult_() { return T{ 1 }; }

template<typename T, T N0, T...N>
requires std::is_arithmetic_v<T>
constexpr T mult_() {
	T x{ N0 };
	x *= mult_<T, N...>();
	return x;
}
