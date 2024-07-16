#pragma once
#include <array>

//template<typename...Ts, template<Ts agrs>  class ... Class>
//void make_it() {
//
//}

template<typename T1, typename T2, T1 ... T1arg, T2 ... T2arg> 
constexpr auto make_it() {
	std::array<T1, sizeof...(T1arg)> arrayT1{ T1arg... };
	std::array<T2, sizeof...(T2arg)> arrayT2{ T2arg... };

	return std::make_pair(arrayT1, arrayT2);
}


//template<typename T1, typename T2, T1... T1arg, T2...T2arg>
//struct Make_It {
//
//};

