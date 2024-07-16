#pragma once


// COMPILE TIME ABSOLUTE VALUE META-FUNCTION -------------------------------------------
template<int N>
struct Abs {
	static_assert(N != INT_MIN);   // C++ 17 STYLE GUARD
	static constexpr int value = (N < 0) ? -N : N; // RETURN

};

//--------------------------------------------------------------------------------------

template<int N>
struct Factorial {
	static_assert(N > 0);
	static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
	static constexpr int value = 1;
};

//---------------------- Mata function factorial -----------------------------------------

template<int N> 
constexpr int Factorial_() {
	return Factorial<N>::value;
}

template<typename T, T x, T y>
struct Sum_ { static const T value = x + y; };

template<typename T, T x, T y>
struct Div_ { static const T value = x / y; };

template<typename T, T x, T y>
struct Mult_ { static const T value = x * y; };

template<typename T>
constexpr int _Sum(T x, T y) {
	return x + y;
}

//////////////////// POWER OF n TO m ////////////////////////////////////////////////////

template<int N,	int M>
struct POWER { static const int value = N * POWER<N, M - 1>::value; };

template<int N>
struct POWER<N, 1> { static const int value = N; };

template<int N>
struct POWER<N, 0> { static const int value = 1; };

template<int64_t N, int64_t M>
struct POWER64 { static const int64_t value = N * POWER64<N, M - 1>::value; };

template<int64_t N>
struct POWER64<N, 1> { static const int64_t value = N; };

template<int64_t N>
struct POWER64<N, 0> { static const int64_t value = 1; };


//////////////////// SUM OF SEQUENCE OF INTEGER /////////////////////////////////////////

template<int N> 
struct SUM_n { static const int value = N + SUM_n<N - 1>::value; };

template<> 
struct SUM_n<1> {  static const int  value = 1; };

template<int N>
struct SUM_n2 { static const int value = N * N + SUM_n2<N - 1>::value; };

template<>
struct SUM_n2<1> { static const int value = 1; };

// GENERALIZATION  OF POWER OF SEQUENCE OF INTEGER POWER TO M 
template<int N, int M>
struct SUM_nm { static const int value = POWER<N, M>::value +SUM_nm<N - 1, M>::value; };

template<int M>
struct SUM_nm<1, M> { static const int value = 1; };

// GENERALIZATION  OF POWER OF SEQUENCE OF INTEGER POWER TO M  for int64_t
template<int64_t N, int64_t M>
struct SUM64_nm { static const int64_t value = POWER64<N, M>::value + SUM64_nm<N - 1, M>::value; };

template<int64_t M>
struct SUM64_nm<1, M> { static const int64_t value = 1; };


///////////////////////////////////////////// END ////////////////////////////////////////

/////////////////////////// Log2 /////////////////////////////////////////////////////////

template<size_t N> 
struct _Log2 {
	enum {
		value = 
	    (((N & 0xFFFFFFFF00000000UL) != 0) << 5) |
		(((N & 0xFFFF0000FFFF0000UL) != 0) << 4) |
		(((N & 0xFF00FF00FF00FF00UL) != 0) << 3) |
		(((N & 0xF0F0F0F0F0F0F0F0UL) != 0) << 2) |
		(((N & 0xCCCCCCCCCCCCCCCCUL) != 0) << 1) |
		((N & 0xAAAAAAAAAAAAAAAAUL) != 0)
	};
};

//////////////////////////// Power of double ///////////////////////////////////
template<size_t N>
struct Pow {
	double operator() (double x) const { return x * Pow<N - 1>()(x); }
};

template<>
struct Pow<1> {
	double operator()(double x) const { return x; }
};

template<>
struct Pow<0> {
	double operator()(double x)const { return 1; }
};