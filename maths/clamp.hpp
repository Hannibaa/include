#pragma once
#include <utility>
#include <array>
#include <include/metaprogramming/my_metaprog.h>

namespace math {


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//				SAMPLE CLAMP FUNCTION 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename X>
	void clamp(X& x, const X& min, const X& max)
	{
		if (x < min) x = min;
		if (x >= max) x = max;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   clip object assossiated to ractangle object    
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<size_t NumArgs, typename T>
		requires std::is_arithmetic_v<T>
	class Clamp {

		template<typename U>
		struct MinMax
		{
			U min;
			U max;
		};


	public:
		using value_type = T;

		Clamp(std::initializer_list<T> _list)
			:_nargs{ NumArgs }
		{
			// list size should be multiple 2
			if (_list.size() % 2 == 0)
			{
				if (2 * _nargs == _list.size())
				{
					int i{};
					for (auto& e : _minmax)
					{
						e.min = *(_list.begin() + i);
						e.max = *(_list.begin() + ++i );
						++i;
					}
				}
				else
				{
					std::runtime_error("Error : requirement between number of argument and lists");
				}

			}
			else
			{
				std::runtime_error("Error : number of values in list should be even");
			}

		}


		void operator()(T& x) {
			_clamp(x, _minmax[0].min, _minmax[1].max);
		}

		void operator()(T& x, T& y) {
			_clamp(x, _minmax[0].min, _minmax[1].max);
			_clamp(y, _minmax[2].min, _minmax[3].max);
		}

		//template<typename ...Xs>
		//requires meta::are_same_v<value_type,Xs...> && (sizeof...(Xs) == NumArgs)
		//void operator() (Xs&...xs)
		//{
		//	std::tuple<Xs...>  XX = std::make_tuple<Xs...>(std::forward<Xs>(xs)...);
		//	(
		//		clamp(xs, 
		//			_minmax[meta::Npack<Xs>::index].min, 
		//			_minmax[i].max),...);
		//}

		virtual ~Clamp() = default;

	private:

		template<typename X>
		void _clamp(X& x, const X& min, const X& max)
		{
			if (x < min) x = min;
			if (x >= max) x = max;
		}

		size_t									_nargs;
		std::array<MinMax<T>, NumArgs>			_minmax;
	};


}