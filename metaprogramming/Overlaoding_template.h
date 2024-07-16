#pragma once
#include <sstream>

template<typename T>               // only regular time required;
std::string make_string(T x) {
	std::cout << "make_string(T x)\n";
	std::stringstream ss;
	
	ss << x;

	return ss.str();
}

template<>
std::string make_string<int>(int x) { std::cout << "make_string(int x)\n"; return std::string{ "this Integer" }; }

template<typename T, typename S>
std::string make_string(T x, S y) {
	std::cout << "make_string(T x, S y)\n";
	std::stringstream ss;
	ss << x << " " << y;

	return ss.str();
}

template<typename T>
std::string make_string(T x, std::string str) {
	std::cout << "make_string(T x, string str)\n";

	return str;
}

template<typename T>
int make_string(T* x, int y) {
	std::cout << "make_string(T* x, int y)\n";
	std::cout << "Adress of pointer is " << x << std::endl;
	return y;
}