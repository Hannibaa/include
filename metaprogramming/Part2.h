#pragma once

//---- implementation of remove const and remove volatitle, and remove_cv_t



template<typename T, T v>
struct integral_constant_ {
	static constexpr T value = v;
	constexpr   operator T () const noexcept { return value; }
	constexpr T operator ()() const noexcept { return value; }
};

// rank of array type :
// primary template handle scalar (non array> types as base case:
template<typename T>
struct rank_ : integral_constant_<size_t, 0u> {};

// partial specialization recognizes bounded array types :
template<typename U, size_t N>
struct rank_<U[N]>
	:integral_constant_<size_t, 1u + rank_<U>::value> {};

// partial specialization recongnizes unbounded array types :
 template<typename U>
 struct rank_<U[]> 
	 : integral_constant_<size_t, 1u + rank_<U>::value> {};

 template<bool b>
 using bool_constant_ = integral_constant_<bool, b>;

 using  true_type_ = bool_constant_<true>;
 using false_type_ = bool_constant_<false>;

 template<typename T>
 struct is_void_ : false_type_ {};
  
 template<> struct is_void_<void> : true_type_ {};
 template<> struct is_void_<void const> :true_type_ {};
 template<> struct is_void_<void volatile > :true_type_ {};
 template<> struct is_void_<void const volatile> :true_type_ {};

 template<class T,class U> struct is_same_ : false_type_ {};
 template<class T> struct is_same_<T,T> :true_type_{};


