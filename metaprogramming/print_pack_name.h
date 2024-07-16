#pragma once
#include <string>
#include <array>

template<typename T>
void printTypeName() {
	std::cout << "Type Name : " << typeid(T).name() << "\n";
}

template<typename T>
void printTypeName(const T& t) {
	std::cout << "Type Name : " << typeid(T).name() << "\n";
}


template<template<typename...> class Class, typename...Ts>
constexpr void printPackName(const Class<Ts...>& C) {
	if (sizeof...(Ts) == 0) { std::cout << "Pack names is empty\n"; return; }
//	std::array<std::string, sizeof...(Ts)> a{ std::string(typeid(Ts).name())... };
	//for (int i = 0; i < sizeof...(Ts); i++)
	//{
	//	std::cout << a[i] << '\n';
	//} old version

	int i[] = { (std::cout << typeid(Ts).name() << '\n', 0)... };
}

template<typename T> 
constexpr void printPackName() {
	printPackName(T{});
}