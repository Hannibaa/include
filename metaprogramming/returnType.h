#pragma once
#include <functional>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    return type of function
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template< typename >
struct Res{};

template<typename R,typename ...Args>
struct Res<R(Args...)> {
	using return_type = R;
};

template<typename M, typename T>
auto foo(M T::* pm) -> Res<M>::return_type;

template<typename F>
auto faa(F* f) -> Res<F>::return_type;

template<typename M, typename T>
auto fee(M T::* pm) -> std::function<M>::result_type;