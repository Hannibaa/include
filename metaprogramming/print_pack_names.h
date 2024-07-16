#pragma once
#include <type_traits>
#include <functional>

struct nullstruct {};

struct helper {
	template<typename...Ts>
	helper(Ts&&...){}
};

template<typename...Ts>
void printPackNames(const Ts&...ts) {
	helper((std::cout << typeid(ts).name() << '\n', 0)...);
}

template<template<typename...> class Class, typename...Ts>
void printPackNames(const Class<Ts...>& ) {
	helper((std::cout << typeid(Ts).name() << '\n', 0)...);
}

template<typename T, typename...Ts>
void printPackName(std::function<T(Ts...)>& ) {
	std::cout << "Return type : " << typeid(T).name() << '\n';
	helper((std::cout << typeid(Ts).name() << '\n', 0)...);
}