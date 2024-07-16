#pragma once
#include <string>
#include <sstream>

template<typename T, typename U>    //  this main function
std::string make_str(T x, U y) {
	std::cout << "Generalization\n";
	std::stringstream ss;
	ss << x << " " << y;

	return ss.str();
}

template<typename T>               // this overloading
std::string make_str(T x, int y) {
	std::cout << "partial specialization\n";

	return std::string("hello;");
}

