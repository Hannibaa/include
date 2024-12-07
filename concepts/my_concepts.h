#pragma once
#include <type_traits>
#include <concepts>
#include <include/metaprogramming/my_metaprog.h>

// some metaprogramming 

namespace Concept {



#define REQUERES(_Class, _Type ,_Function)  requires(_Class C,_Type value){ C._Function(value);}
#define MAKE_HAS_FUNCTION(_Class, _Type, _Function) template<typename _Class, typename _Type> \
          concept  Has_##_Function = REQUERES(_Class, _Type, _Function)                       \

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CONCEPTS 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// NEGATIVE AND POSITIVE
	template<typename T, T x>
	concept Negative = x < static_cast<T>(0);

	template<typename T, T y>
	concept Positive = y > static_cast<T>(0);

	// concepte of post increment 
	template<typename T>
	concept Pre_Incrementable  = requires(T r) { ++r; };

	template<typename T>
	concept Post_Incrementable = requires(T r) { r++; };

	template<typename T>
	concept Pre_Decrementable  = requires(T r) { --r; };

	template<typename T>
	concept Post_Decrementable = requires(T r) { r--; };

	// concept of size of
	template<typename T, size_t N>
	concept SizeOf = (sizeof(T) == N);



	// concepts Addable
	template<typename...Args>
	concept Addable = requires(Args...args)
	{
		(... + args);
			requires meta::are_same_v<Args...>;
			requires sizeof...(Args) > 1;
		{(... + args)} noexcept -> std::same_as<meta::first_arg_t<Args...>>;
	};





	template< typename Container, typename T>
	concept HasPushBack = requires (Container t, T value) {

		t.push_back(value);
	};

	template<typename Container>
	concept HasPushBack2 = requires(Container C, typename Container::value_type value) {
		C.push_back(value);
	};

	template<typename Container>
	concept HasPushBack3 = requires(Container C) {
		C.push_back(std::declval<typename Container::value_type&>());
	};

	namespace Coordinate {
		// 0. hase composante x, y ro X, Y
		template<typename Coord>
		concept has_XY = requires(Coord coord)
		{
			coord.x;
			coord.y;
		};

		template<typename Coord>
		concept has_xy = requires(Coord coord)
		{
			coord.X;
			coord.Y;
		};
	}

	namespace Rectangle {
		template<typename RECT>
		concept is_rect = requires(RECT rect)
		{
			rect.x;
			rect.y;
			rect.dx;
			rect.dy;
		};
	}

	// 1. check if class has x and y variable or X, y
	template<typename V>
	concept is_geometrical_vector = requires(V v)
	{
		typename V::value_type;
		requires std::is_arithmetic_v<typename V::value_type>;
		v.x;
		v.y;
		v + v;
		v - v;
		{ (v * v) } -> std::convertible_to<typename V::value_type>;
	};

}
