#pragma once
#include <wincontypes.h>
/*
					Class for Vector 2 dimension
*/
#include <algorithm>
#include <cmath>

namespace geom2d {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //   Vector Class definition   
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct Vector2d {
		static_assert(std::is_arithmetic_v<T>, "Type T should be arithmetic type");
		T x;
		T y;

		using value_type = T;

		Vector2d(T _x = T{}, T _y = T{})
			: x{ _x }, y{ _y }
		{}

		template<typename U>
		Vector2d(const Vector2d<T>& vec)
			: x{ static_cast<U>(vec.x) }
			, y{ static_cast<U>(vec.y) }
		{}

		Vector2d(const COORD& coord)
			: x{ static_cast<T>(coord.X) }
			, y{ static_cast<T>(coord.Y) }
		{}

		template<typename U>
		Vector2d<U> as() const {
			return Vector2d<U>{static_cast<U>(x), static_cast<U>(x)};
		}

		constexpr T Norm() const {
			return std::sqrt(x * x + y * y);
		}

		template<typename U>
		void clamped(U xmin, U xmax, U ymin, U ymax) {
			x = static_cast<T>(std::clamp<U>(x, xmin, xmax));
			y = static_cast<T>(std::clamp<U>(y, ymin, ymax));
		}

		bool operator == (const Vector2d p) {
			return this->x == p.x && this->y == p.y;
		}

	};

	template<typename T>
	inline Vector2d<T> operator - (const Vector2d<T>& lhv, const Vector2d<T>& rhv) {
		return Vector2d<T>{ lhv.x - rhv.x, lhv.y - rhv.y };
	}

	template<typename T>
	inline Vector2d<T> operator + (const Vector2d<T>& lv, const Vector2d<T>& rv) {
		return Vector2d<T>{ lv.x + rv.x, lv.y + rv.y };
	}

	template<typename T, typename Scalar>
	inline Vector2d<T> operator * (const Scalar& scalar, const Vector2d<T>& point) {
		return Vector2d<T>(scalar * point.x, scalar * point.y);
	}

	template<typename T, typename Scalar>
	inline Vector2d<T> operator * (const Vector2d<T>& point, const Scalar& scalar) {
		return Vector2d<T>(scalar * point.x, scalar * point.y);
	}

	template<typename T, typename Scalar>
	inline Vector2d<T> operator / (const Vector2d<T>& point, const Scalar& scalar) {
		return Vector2d<T>(point.x / scalar, point.y / scalar);
	}

}

// Predefined 
using fVec2  = geom2d::Vector2d<float>;
using iVec2  = geom2d::Vector2d<int>;
using uiVec2 = geom2d::Vector2d<unsigned int>;
using sVec2  = geom2d::Vector2d<short>;
using usVec2 = geom2d::Vector2d<unsigned short>;

