#pragma once

template<typename T, int N>
class Vec {

	T x[N]{};

public:

	T& operator[](int index) { if (index > N - 1 || index < 0) { std::cout << "out of range\n"; return x[0]; }; return x[index]; }
	void identify() { std::cout << "primary template \n"; }
};

template<typename T>
class Vec<T, 1> {
	T x;
public:
	Vec() = default;
	Vec(T _x) : x{_x}{}
	T& value() { return x; }
};

template<typename T , int N>
class Vec<T const, N> {

	T x[N]{ 1 };

public:

	const T& operator[](int index) { if (index > N - 1 || index < 0) { std::cout << "out of range\n"; return x[0]; }; return x[index]; }
	void identify() { std::cout << "T const specialization\n "; }
};

template<typename T, int N>
class Vec<T*, N>{

public:
	Vec() { std::cout << " pointer raw \n"; }
};

