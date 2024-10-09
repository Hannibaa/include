#pragma once
/*
					Rectangle Header file 
						Rect Class 
						Box  Class
*/

#include <include/geometry/vector2d.hpp>


namespace   geom2d {

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Rectangle definition 
    // 	  by First Point (x,y) and length dx and width dy
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct Rect {
		static_assert(std::is_arithmetic_v<T>, "Type T should be arithmetic type");
		T x;
		T y;
		T dx;
		T dy;

		typedef  T						value_type;
		typedef  geom2d::Vector2d<T>	vector_type;


		Rect() :x{}, y{}, dx{}, dy{} {}

		Rect(T _x, T _y, T _dx, T _dy)
			: x{ _x }
			, y{ _y }
			, dx{ _dx }
			, dy{ _dy }
		{}

		Rect(const Vector2d<T>& p1, const Vector2d<T>& p2)
			:x{ min(p1.x, p2.x) }
			, y{ min(p1.y, p2.y) }
		{
			dx = max(p1.x, p2.x) - x;
			dy = max(p1.y, p2.y) - y;
		}


		template<typename U>
		explicit Rect(const Rect<U>& rect)
			: x{ static_cast<T>(rect.x) }
			, y{ static_cast<T>(rect.y) }
			, dx{ static_cast<T>(rect.dx) }
			, dy{ static_cast<T>(rect.dy) }
		{}

		void set_rectangle(T _x, T _y, T _dx, T _dy) {
			x = _x; y = _y; dx = _dx; dy = _dy;
		}

		template<typename U>
		void set_rectangle(const Rect<U>& rect)
		{
			x = static_cast<T>(rect.x);
			y = static_cast<T>(rect.y);
			dx = static_cast<T>(rect.dx);
			dy = static_cast<T>(rect.dy);
		}

		Vector2d<T> get_position() const {
			return Vector2d<T>(x, y);
		}

		void set_position(const Vector2d<T>& vec) {
			x = vec.x;
			y = vec.y;
		}

		void set_position(T _x, T _y) {
			x = _x;
			y = _y;
		}

		template<typename U>
		Rect<U> as() {
			return Rect<U>{static_cast<U>(x), static_cast<U>(y),
				static_cast<U>(dx), static_cast<U>(dy)};
		}

		bool contain(T _x, T _y) const {
			return (_x >= x && _x < x + dx) &&
				(_y >= y && _y < y + dy);
		}

		bool contain(const Vector2d<T>& p) const {
			return contain(p.x, p.y);
		}

		template<typename U>
		bool contain(const Vector2d<U>& p) const {
			return contain(p.as<T>());
		}

		// collision const
		bool is_collid(const Rect<T>& rect) const {
			return contain(rect.x, rect.y) ||
				contain(rect.x + rect.dx - 1, rect.y) ||
				contain(rect.x, rect.y + rect.dy - 1) ||
				contain(rect.x + rect.dx - 1, rect.y + rect.dy - 1);
		}

		// collision const
		bool is_collid(const Rect<T>& rect) {
			return contain(rect.x, rect.y) ||
				contain(rect.x + rect.dx - 1, rect.y) ||
				contain(rect.x, rect.y + rect.dy - 1) ||
				contain(rect.x + rect.dx - 1, rect.y + rect.dy - 1);
		}

		// shrink and expand by equal distance

		Rect shrink(const T& d) const {
			return Rect(x + d, y + d, dx - T(2) * d, dy - T(2) * d);
		}

		Rect expand(const T& d) {
			return Rect(x - d, y - d, dx + T(2) * d, dy + T(2) * d);
		}

	};

}

using iRect = geom2d::Rect<int>;
using fRect = geom2d::Rect<float>;
using dRect = geom2d::Rect<double>;
using sRect = geom2d::Rect<short>;
using usRect = geom2d::Rect<unsigned short>;
using uiRect = geom2d::Rect<unsigned int>;
