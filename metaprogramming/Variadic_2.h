#pragma once
#include <array>
#include <string>

struct TT {

};

template<typename T>
struct TypeName : TT {
	using Type = T;
};

struct Typename {

};


template<typename ...Ts>
constexpr auto get_type() {
	return std::array<TT*, sizeof...(Ts)>{new TypeName<Ts> ...};
	 
}

template<typename ...Ts>
constexpr auto get_type_sizes() {
	return std::array<size_t, sizeof...(Ts)>{sizeof(Ts)...};
}

template<typename ...Ts>
constexpr auto get_type_names() {
	return std::array<std::string, sizeof...(Ts)>{std::string(typeid(Ts).name())...};
}

template<typename ...Ts>
constexpr auto get_type_sizes_names() {
	return std::array<std::pair<std::string, size_t>, sizeof...(Ts)>{
		std::make_pair(std::string(typeid(Ts).name()), sizeof(Ts))...};
}


template<typename T, T...tpack>
constexpr auto make_array_pack() {

	return std::array<T, sizeof...(tpack)>{tpack...};
}

template<typename T, T...tpack>
auto make_test() {

	auto a = make_array_pack<T, tpack...>();
	
	return a;
}

template<typename ...T1, typename ...T2>
auto test(T1...arg1,T2 ...arg2) {
	std::cout << " first pack " << sizeof...(T1) << '\n';
	std::cout << " second pack " << sizeof...(T2) << '\n';

}
