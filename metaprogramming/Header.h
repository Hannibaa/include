#pragma once

 
// NATURAL NUMBER TYPE
template<typename T>
struct is_natural_number { static const bool value = false; };

template<>
struct is_natural_number<int> { static const bool value = true; };
template<>
struct is_natural_number<uint32_t> { const bool value = true; };
template<>
struct is_natural_number<int64_t> { const bool value = true; };
template<>
struct is_natural_number<uint64_t> { const bool value = true; };
template<>
struct is_natural_number<short> { const bool value = true; };

// ARRAY TYPE
template<class T>
struct rank_ {
	static size_t const value = 0u;
};

template<class U,size_t N>
struct rank_ <U[N]> {
	static size_t const value = 1u + rank_<U>::value;
};

//template<typename T, T x>
//bool is_natural_number_f() {
//	if (is_natural_number<T>::value) return true; return false;
//}

//A metafunction can also produce a type as its result
// remove const-qualification ;
// No real removal; give me the equivalent type without const.

// primary template handles types that are not const-qualified:
template<class T>
struct remove_const_ { using type = T; }; // identity

// partial specialization recognizes const-qualified types:
template<class U>
struct remove_const_<U const> { using type = U; };
 
// Identity metafunction 
template<class T>
struct type_is_ { using type = T; };

// Can now apply the convention via inheritance:
// primary template handles types that are not volatile-qualified:
template<class T>
struct remove_volatile_ : type_is_<T> {}; // identity;

// partial specialization recognizes volatile-qualified types:
template<class U>
struct remove_volatile_<U volatile> :type_is_ <U>{};

// Compile-time decision making
// IF and IF_t to select one of two types:
// self-configuring code;


// 1. assume : int const q = 23;
// 2. IF_<(),int , unsigned> k; // k declared to have 1 of these 2 integer types
// 3. IF_<(),F,G>{}() ; // instantiate and call 1 of these 2 function objects
// 4. class D : public IF_<(),B1,B2>{...}; // inherit from 1 of these 2 base classes

// primary template assumes the bool value is true;
template<bool p,class T,class> // needn't name unused param's
struct IF_ :type_is_<T> {};

//partial specialization recognizes a false value;
template<class T, class F>
struct IF_<false, T,F> :type_is_<F> {};

//...............................................................................
// primary template
template<int kind,class T, class P, class >
struct Kind { using type = T(*)(P); };

// partial specialization 
template<class T, class P, class R>
struct Kind<1, T, P, R> { using type = P(*)(T); };

template<class T, class P, class R>
struct Kind<2, T, P, R> { using type = R(*)(T,P); };

// SFINAE :Substitution Failure Is Not An Error.
// A single type variation on condition
// if true , use the given type; if false, use no type at all:
// primary
template <bool, class T = void>
struct enable_if_ : type_is_<T> {};

//partial initialization
template<class T>
struct enable_if_<false, T> {};

//----------------------------------------------------------------------------
template <typename T>
struct is_natural_number_ {  };

// pqrtial specialization
template<>
struct is_natural_number_<short> : type_is_<short> {};

template<>
struct is_natural_number_<int> : type_is_<int> {};

template<>
struct is_natural_number_<long int>:type_is_<long int>{};

template<> 
struct is_natural_number_<long long int>:type_is_<long long int>{};

template<>
struct is_natural_number_<unsigned short>:type_is_<unsigned short>{};

template<>
struct is_natural_number_<unsigned int> : type_is_<unsigned int> {};

template<>
struct is_natural_number_<unsigned long int> :type_is_<unsigned long int> {};

template<>
struct is_natural_number_<unsigned long long int> :type_is_<unsigned long long int> {};

