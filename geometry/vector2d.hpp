#pragma once
/*
					Class for Vector 2 dimension
*/
#include <algorithm>
#include <cmath>
#include <include/concepts/my_concepts.h>

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

		//template<typename Coord>
		//requires Concept::Coordinate::has_xy<Coord>
		//Vector2d(const Coord& coord)
		//	: x{ static_cast<T>(coord.x) }
		//	, y{ static_cast<T>(coord.y) }
		//{}

		//template<typename Coord>
		//requires Concept::Coordinate::has_XY<Coord>
		//Vector2d(const Coord& coord)
		//	: x{ static_cast<T>(coord.X) }
		//	, y{ static_cast<T>(coord.Y) }
		//{}

		template<typename U>
		Vector2d<U> as() const {
			return Vector2d<U>{static_cast<U>(x), static_cast<U>(y)};
		}

		Vector2d polar() const {
			return Vector2d(Norm(), Angle());
		}

		Vector2d cartesian() const {
			return Vector2d(x * std::cos(y), x * std::sin(y));
		}

		constexpr T Norm() const {
			return std::sqrt(x * x + y * y);
		}

		constexpr T Angle() const {
			return std::atan2(y, x);
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

	// - operation
	template<typename T>
	inline Vector2d<T> operator - (const Vector2d<T>& lhv, const Vector2d<T>& rhv) {
		return Vector2d<T>{ lhv.x - rhv.x, lhv.y - rhv.y };
	}

	// + operation
	template<typename T>
	inline Vector2d<T> operator + (const Vector2d<T>& lv, const Vector2d<T>& rv) {
		return Vector2d<T>{ lv.x + rv.x, lv.y + rv.y };
	}

	// Scalar Product
	template<typename T>
	inline T operator * (const Vector2d<T>& lv, const Vector2d<T>& rv) {
		return lv.x * rv.x + lv.y * rv.y;
	}

	// scalar product vector
	template<typename T, typename Scalar>
	requires std::is_arithmetic_v<Scalar>
	inline Vector2d<T> operator * (const Scalar& scalar, const Vector2d<T>& point) {
		return Vector2d<T>(T(scalar) * point.x, T(scalar) * point.y);
	}

	// scalar left product vector
	template<typename T, typename Scalar>
	requires std::is_arithmetic_v<Scalar>
	inline Vector2d<T> operator * (const Vector2d<T>& point, const Scalar& scalar) {
		return Vector2d<T>(T(scalar) * point.x, T(scalar) * point.y);
	}

	// division to scalar
	template<typename T, typename Scalar>
	requires std::is_arithmetic_v<Scalar>
	inline Vector2d<T> operator / (const Vector2d<T>& point, const Scalar& scalar) {
		return Vector2d<T>(point.x / scalar, point.y / scalar);
	}

	// Determinant made by two victor
	template<typename T>
	inline T operator | (const Vector2d<T>& v1, const Vector2d<T>& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	// predefined functions
	template<typename T, typename Float>
	requires std::is_floating_point_v<Float>
	Vector2d<T> rot(const Vector2d<T>& v, Float theta)
	{
		return Vector2d<T>(v.x * std::cos(theta) - v.y * std::sin(theta),
			v.x * std::sin(theta) + v.y * std::cos(theta));
	}

	template<typename T>
	Vector2d<T> normal(const Vector2d<T>& v) {
		return Vector2d<T>(-v.y, v.x);
	}

	template<typename T>
	std::ostream& operator << (std::ostream& os, const Vector2d<T>& v)
	{
		os << "( " << v.x << " , " << v.y << " )";
		return os;
	}

	template<typename T, typename Coord>
	Vector2d<T>  as(const Coord& coord) {
		return Vector2d<T>(static_cast<T>(coord.X), static_cast<T>(coord.Y));
	}
}

// Predefined 
using fVec2  = geom2d::Vector2d<float>;
using iVec2  = geom2d::Vector2d<int>;
using uiVec2 = geom2d::Vector2d<unsigned int>;
using sVec2  = geom2d::Vector2d<short>;
using usVec2 = geom2d::Vector2d<unsigned short>;

