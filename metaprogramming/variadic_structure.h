#pragma once
#include <vector>
#include "Variadic_4.h"

template<typename T, int N>
struct arg { T t; };

template<typename ...Ts>
struct Args {
	arg<Ts, N>...;
};

template<typename...Ts>
struct var_list {
	void* a[sizeof...(Ts)];

	auto& operator [] (const int N) { return static_cast<type_index<N, Ts...>::type*>(a[N]); }
};