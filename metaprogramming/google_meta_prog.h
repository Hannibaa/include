#pragma once

/*
	   global math functions filtering base

	   - What it does :
	   - Defines a typedef 'type' as follows:
	   - # if type T has a member typedef Eigen_BaseClassForSpecializationOfGlobalMathFuncImpl, than
	   - global_math_functions_filtering_base<T>::type is a typedef for T.
	   -
	   - How it's used :
	   - To allow to defined the global math functions (like sin...) in certain cases, like the Array expression.
	   - When you do sin(array1 + array2), the object array1+array2 has a complicated expression type, all what you
	   - want to know is that it inherits ArrayBase. So we implement a partial specializatio of sin_impl<Derived>,
	   - otherwise our partial specialization
	   - So we must make sure to use sin_impl<ArrayBase<Derived>> and not sin_impl<Derived>, otherwize our partial
	   - specialization won't be used. how does sin know that? That's exactly what global_math_functions_filtering_base
	   - tell it.
	   -
	   - How it's implemented:
	   - SFINAE in the style of enable_if. Highly susceptible of breaking compilers. With GCC, it sure does work, but
	   - if you replace the typename dummy by an integer template parameter, it doesn't work anymore!

*/

template<typename T, typename dummy = void>
struct global
{
	typedef T type;
};

template<typename T> struct always_void { typedef void type; };

template<typename T>
struct global
	< T,
	   typename always_void<typename T::Base>::type
	>
{
	typedef typename T::Base type;
};