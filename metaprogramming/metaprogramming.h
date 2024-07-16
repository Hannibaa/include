#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <tuple>
#include <type_traits>

/////////////////////////////////// HAS TYPE STRUCTURE //////////////////////////////

template<typename T>
struct has_type {
	using type = T;
};

//////////////////////////////////////// IF /////////////////////////////////////////

template<bool condition, typename Then, typename Else>
struct if_;

template<typename Then, typename Else>
struct if_<true, Then, Else> {
	using type = Then;
};

template<typename Then, typename Else>
struct if_<false, Then, Else> {
	using type = Else;
};

///////////////////////////// TYPE LIST ///////////////////////////////////////////////////////////

template<typename ...>
struct type_list{};


//////////////////////////// empty list //////////////////////////////////////////////////////////

template<typename LIST>
struct empty : std::false_type{};

template<template<typename...>class List>
struct empty<List<>> : std::true_type{};

template<typename List>
static constexpr bool empty_v = empty<List>::value;

//////////////////////////// front list //////////////////////////////////////////////////////////

template<typename LIST>
struct front;

template<template<typename...> class Class,typename T0, typename ...Ts>
struct front<Class<T0, Ts...>> {
	using type = T0;
};

template<typename LIST>
using front_t = typename front<LIST>::type; 

//////////////////////////// pop_front list //////////////////////////////////////////////////////////

template<typename LIST> 
struct pop_front;

template<template<typename...>class Class ,typename T0, typename ...Ts>
struct pop_front<Class<T0, Ts...>> {
	using type = Class<Ts...>;
};

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

///////////////////////////// Contain type ///////////////////////////////////////////////////////////

//template<typename SEARCH, typename LIST>
//struct contain_type : 
//	if_

///////////////////////////// Get Pack or type ///////////////////////////////////////////////////////

template<template<typename...>class Class, typename...Ts>
type_list<Ts...> getPack(const Class<Ts...>&) {
	return type_list<Ts...>{};
}

////////////////////////////////// AT ////////////////////////////////////////////////////////////

template<typename LIST, size_t index>
struct at : has_type<typename at<pop_front_t<LIST>, index - 1>::type> {};

template<typename LIST>
struct at<LIST, 0> :has_type<front_t<LIST>> {};

template<typename LIST, size_t index>
using at_t = typename at<LIST, index>::type;

///////////////////////////////// BACK ///////////////////////////////////////////////////////////

template<typename LIST>
struct back : has_type<typename back<pop_front_t<LIST>>::type>{};

template<template<typename...> class Class, typename T0>
struct back<Class<T0>> : has_type<T0>{};

template<typename LIST>
using back_t = typename back<LIST>::type;

///////////////////////////// PUSH BACK ///////////////////////////////////////////////////////////

template<typename LIST, typename T>
struct push_back;

template<template<typename...> class Class, typename ...Ts, typename T>
struct push_back<Class<Ts...>,T> : has_type<Class<Ts...,T>>{};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

///////////////////////////// POP BACK //////////////////////////////////////////////////////////

template<typename List, typename rlist = type_list<> >
struct pop_back;

template<template<typename...>class Class, typename T0 , typename Rlist>
struct pop_back<Class<T0>, Rlist> : has_type<Rlist> {};

template<template<typename...>class Class,typename T0,typename T1, typename...T2TN, typename Rlist>
struct pop_back< Class<T0,T1, T2TN...> , Rlist> :
	       pop_back< Class<T1, T2TN...>, push_back<Rlist,T0>>{};

template<typename List>
using pop_back_t = typename pop_back<List>::type;

////////////////////////////////////////// ANY /////////////////////////////////////////////////////

