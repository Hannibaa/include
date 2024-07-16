#pragma once
// FUNCTION TYPE SPECIALIZATION 
template<typename T, typename ReturnT>
struct function {
	using typeFvalue = ReturnT(*)(T);
	using typeFref = ReturnT(*)(T&);
	using typeFconstRef = ReturnT(*)(const T&);
};

template<>
struct function<void, void> {
	using typeFvalue = void (*)(void);
};

template<typename T, typename S, typename R>
struct function2 {
	using type = R(*)(T, S);
};

template<typename T, typename S>
T G(T x, S y, typename function2<T, S, T>::type f) {
	return f(x,y);
}