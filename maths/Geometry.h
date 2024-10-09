#pragma once
#include <algorithm>
#include <cmath>
#include <numbers>


// Constant pi
constexpr inline float Pi = static_cast<float>(std::numbers::pi);
constexpr inline float Pi2 = Pi / 2.f;


namespace geom2d {

	// Rotating inside wstring or string as it is string

	int _rot(int n, int lx) {
		int k = n % lx;
		return lx * (lx - 1) - lx * k + (n - k) / lx;
	}

	int _rot90d(int N, int lx, int ly) {
		int k = N % ly;
		return (N - k) / ly + (ly - 1 - k) * lx;
	}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//   Point Class definition   
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct Point2d {
		static_assert(std::is_arithmetic_v<T>, "Type T should be arithmetic type");
		T x;
		T y;

		using value_type = T;

		Point2d(T _x = T{}, T _y = T{})
			: x{ _x }, y{ _y }
		{}

		template<typename CoordType>
		Point2d(const CoordType& coord)
			:x{static_cast<T>(coord.X)}
			,y{static_cast<T>(coord.Y)}
		{}

		template<typename U>
		Point2d<U> as() {
			return Point2d<U>{static_cast<U>(x), static_cast<U>(x)};
		}

		template<typename U>
		void clamped(U xmin, U xmax, U ymin, U ymax) {
			x = static_cast<T>(std::clamp<U>(x, xmin, xmax));
			y = static_cast<T>(std::clamp<U>(y, ymin, ymax));
		}

		bool operator == (const Point2d p) {
			return this->x == p.x && this->y == p.y;
		}
		                                                                
	};

	template<typename T>
	inline Point2d<T> operator - (const Point2d<T>& lhv, const Point2d<T>& rhv) {
		return Point2d<T>{ lhv.x - rhv.x, lhv.y - rhv.y };
	}

	template<typename T>
	inline Point2d<T> operator + (const Point2d<T>& lv, const Point2d<T>& rv) {
		return Point2d<T>{ lv.x + rv.x, lv.y + rv.y };
	}

	template<typename T, typename Scalar>
	inline Point2d<T> operator * (const Scalar& scalar, const Point2d<T>& point) {
		return Point2d<T>(scalar * point.x, scalar * point.y);
	}

	template<typename T, typename Scalar>
	inline Point2d<T> operator * (const Point2d<T>& point , const Scalar& scalar ) {
		return Point2d<T>(scalar * point.x, scalar * point.y);
	}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    Line definition
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Vector>
	constexpr Vector normlized(const Vector& vec);

	template<typename Vector>
	struct Line {
		
		Line(const Vector& point, const Vector& direction)
			: p{point}
			, d{direction}
		{}

		static Line make_line(const Vector& point1, const Vector& point2) {
			return Line(point1, geom2d::normlized(point2 - point1));
		}

		Vector p;
		Vector d;
	};


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

		typedef  T  value_type;

		Rect() :x{}, y{}, dx{}, dy{} {}

		Rect(T _x, T _y, T _dx, T _dy)
			: x{ _x }
			, y{ _y }
			, dx{ _dx }
			, dy{ _dy }
		{}

		Rect(const Point2d<T>& p1, const Point2d<T>& p2)
			:x{ min(p1.x, p2.x) }
			,y{ min(p1.y, p2.y) }
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

		template<typename U>
		Rect<U> as() {
			return Rect<U>{static_cast<U>(x), static_cast<U>(y),
				static_cast<U>(dx), static_cast<U>(dy)};
		}

		bool contain(T _x, T _y) const {
			return (_x >= x && _x < x + dx) &&
				(_y >= y && _y < y + dy);
		}

		bool contain(const Point2d<T>& p) const {
			return contain(p.x, p.y);
		}

		// collision
		bool is_collid(const Rect<T>& rect) const {
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

	typedef Rect<float>        fRect;                           // 
	typedef Point2d<float>     fPoint2d;						// 
	typedef Rect<int>          iRect;							// 
	typedef Point2d<int>       iPoint2d;						// 

	// Make vector from two points
	template<typename T>
	Point2d<T>  make_vector(const Point2d<T>& p1, const Point2d<T>& p2) {
		return p2 - p1;
	}

	template<typename Vec>
	void print2d_point(const Vec& vec, std::string_view comment = "") {
		std::cout << comment << ".x = " << vec.x << " .y = " << vec.y << '\n';
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //   Geometry function    
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	constexpr T Norm2(T x, T y) {
		return x * x + y * y;
	}

	template<typename Point>
	constexpr typename Point::value_type Norm2(const Point& p) {
		return Norm2(p.x, p.y);
	}

	template<typename T>
	constexpr T Norm(T x, T y) {
		return std::sqrt(x * x + y * y);
	}

	template<typename Vector>
	constexpr typename Vector::value_type Norm(const Vector& p) {
		return Norm(p.x, p.y);
	}

	// Parpendicular vector or normal to vector vec
	template<typename Vector>
	constexpr typename Vector::value_type Normal_vector(const Vector& vec) {

		return {};
	}

	// Normalization of vector 
	template<typename Vector>
	constexpr Vector normlized(const Vector& vec) {
		auto n = Norm(vec);

		return{(1 / n)*vec};
	}

	template<typename Vector>
	constexpr bool isParpendicular(const Vector& v1, const Vector& v2) {

		return (v1.x * v2.x + v1.y * v2.y) == static_cast<typename Vector::value_type>(0);
	}

	template<typename Vector>
	constexpr bool isParallel(const Vector& v1, const Vector& v2) {

		return v1.x * v2.y - v1.y * v2.x == static_cast<typename Vector::value_type>(0);
	}

	template<typename Point>
	constexpr Point middle_segment(const Point& p1, const Point& p2) {

		return {};
	}

	template<typename Vector, typename Float>
	constexpr Vector rotate_vector(const Vector& vec, Float angle) {

		return {};
	}

	template<typename Vector>
	constexpr Vector translate_vector(const Vector& vec, typename Vector::value_type& value) {

		return {};
	}



}


// predefined type : 
// 1. Vectors
using fVec2 = geom2d::Point2d<float>;
using iVec2 = geom2d::Point2d<int>;
using uiVec2 = geom2d::Point2d<unsigned int>;
using sVec2 = geom2d::Point2d<short>;
using usVec2 = geom2d::Point2d<unsigned short>;

// 2. Rectangles

using iRect = geom2d::Rect<int>;
using fRect = geom2d::Rect<float>;
using sRect = geom2d::Rect<short>;
using usRect = geom2d::Rect<unsigned short>;
using uiRect = geom2d::Rect<unsigned int>;
