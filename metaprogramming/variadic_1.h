#pragma once
#include <array>
#include <stdarg.h>
#include <algorithm>

using namespace std;

template<typename Tsource, typename Tdistination>
Tdistination convert(const Tsource& x) {
	// static assert and concept for these conversion ...
	static_assert(std::is_pod<Tsource>::value && std::is_pod<Tdistination>::value, "Type should be POD");

	if (sizeof(Tsource) != sizeof(Tdistination)) {
		cout << "size of source not equal to size of distination\n";
		return Tdistination{};
	}

	Tdistination* p = (Tdistination*)&x;
	return *p;
}

template<typename Container>
void printVec(Container C) {
	for (int i = 0; i < C.size(); i++) cout << C[i] << " "; cout << '\n';
}

template<typename T, int n>
auto make_array(T x, ...)
{
	if (n == 0) exit(1);

	array<T, n> v;

	va_list a;
	v[0] = x;

	va_start(a, x);

	for (int i = 1; i < n; i++)
	{
		v[i] = va_arg(a, T);
	}

	va_end(a);

	return v;
}

template<typename T0, typename ... T>
constexpr auto make_array_(T...args) {


	return std::array<T0, sizeof...(T)>{T0(args)...};
}

template<typename ...Ts>
constexpr auto get_max_size() {
	return std::max({ sizeof(Ts)... });
}

