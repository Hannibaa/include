#pragma once

template<typename ...Ts>
struct type_list {};

////////////////////////////////// type_index for list //////////////////////////////////////////

template<int N, >
struct get_type {
	using type = typename get_type<N - 1, type_list<Ts...>>::type;
};

////////////////////////////////// type_index ///////////////////////////////////////////////////

template<int N, typename T0, typename ...Ts>
struct type_index {
	using type = typename type_index<N - 1, Ts...>::type;
};

template<typename T0, typename...Ts>
struct type_index<0, T0, Ts...> {
	using type = T0;
};

template<int N,typename...Ts>
using type_index_t = typename type_index<N, Ts...>::type;

////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T, typename...Ts>
type_list<Ts...> pop_type(const type_list<T,Ts...>& l) {
	return type_list<Ts...>{};
}

template<typename T, typename...Ts>
type_list<T, Ts...> push_back() {
	return type_list<T, Ts...>{};
}

//template<typename...Ts, typename T>
//type_list<Ts..., T> push_front() {
//	return type_list<Ts..., T>{};
//}
//

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct Struct {
	T x;
	Struct() = default;
	Struct(const T& _x):x{_x}{}
};

template<typename ...Ts>
struct Tuple : Struct<Ts>... {
	Tuple() = default;
	Tuple(Ts...args):Struct<Ts>{args}...{}

	// operator () or [] return the value of type at index i;
	template<size_t i>
	auto get() { return Struct<typename type_index<i, Ts...>::type>::x; }
};

template<typename T, typename...Ts>
Tuple<Ts...> popType(const Tuple<T, Ts...>& t) {
	return Tuple<Ts...>{ t.Struct<Ts>::x... };
}


template<size_t i, typename ...Ts>
void printTuple(const Tuple<Ts...>& t) {
	static_assert(i < sizeof...(Ts));
	std::cout << "element " << i << " : " << t.Struct<typename type_index<i,Ts...>::type>::x << '\n';
}