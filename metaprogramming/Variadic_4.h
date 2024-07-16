#pragma once
//    get type of maximum sizeof() from pack of types

//template<typename T0, typename ...Ts>
//constexpr auto get_type() {
//	
//};


template<int N, typename T0, typename ...Ts>
struct type_index {
	using type = type_index<N-1,Ts...>::type;
};

template<typename T0, typename...Ts>
struct type_index<0, T0, Ts...> {
	using type = T0;
};

template<typename T0, typename T1>
struct max_size_2type {
	//static_assert(sizeof(T0) == sizeof(T1),"Equal size");
	using type =typename std::conditional < sizeof(T1) < sizeof(T0), T0, T1 > ::type;
};




template<typename T0, typename T1, typename...Ts>
struct max_size_type {
	using type = max_size_type<typename max_size_2type< T0, T1>::type, Ts... >::type ;
};

template<typename T0, typename T1>
struct max_size_type<T0,T1> {
	using type = typename std::conditional < sizeof(T1) < sizeof(T0), T0, T1 > ::type;
};
