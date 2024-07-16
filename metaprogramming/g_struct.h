#pragma once
#include <string>
#include <array>

template<typename T>
void printTypeName_() {
	std::cout << "Type Name : " << typeid(T).name() << "\n";
}

void printTypeName() { std::cout << "----------end----------\n"; }

template<typename T, typename...Ts>
void printTypeName() {
	printTypeName_<T>();
	if (sizeof...(Ts) == 0) return;
	printTypeName<Ts...>();
}


template<typename ...Ts>
struct g_struct {
	void printPackName() {
		std::array<std::string, sizeof...(Ts)> a{ std::string(typeid(Ts).name())... };
		for (int i = 0; i < sizeof...(Ts); i++)
		{
			std::cout << a[i] << '\n';
		}
	}
};

template<template<typename...> class Class, typename...Ts> 
constexpr void PrintPack(const Class<Ts...>& C) {
	std::array<std::string, sizeof...(Ts)> a{ std::string(typeid(Ts).name())... };
	for (int i = 0; i < sizeof...(Ts); i++)
	{
		std::cout << a[i] << '\n';
	}

}


template<typename...Ts ,template<typename...> class Class >
constexpr void PrintPackEx(const Class<Ts...>& C) {
	std::array<std::string, sizeof...(Ts)> a{ std::string(typeid(Ts).name())... };
	for (int i = 0; i < sizeof...(Ts); i++)
	{
		std::cout << a[i] << '\n';
	}

}



