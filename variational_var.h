#pragma once
#include <limits>
#include <chrono>
#include "C:\Users\Acer\source\MyLib\random_generator.h"

/*
       All Class didn't include Timer for speed so we keep it without unit.
	   Make three variable in arithmetic type T after extended to another type that support
		 += ,-=,  < , > , = , operation
		 1. Var_<T> this geos incremented progressive to infinite
		 2. _Var<T> this geos decremented to minus infinite
		 3. _Var_<T> this oscillate between min and max, and have two kind :
			3.1 When reach max start decrementing and when reach min incrementing;
			3.2 Whenm reach max start value directly from min as circulair connection space max-min.
		 4. Var0<T> this value converge to x0 from any where 
		    with speed and decceleration du to drag factor mu, air or solid drag.
*/

template <typename T>
class Var0 {
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");
	T x;
	T x0;
	T m_speed;                        // speed always > 0;
	T m_decceleration;
	bool x_state;

	void update() {
		    x += m_speed;
		if (x_state) {
		    if (x < x0) x = x0;
		}
		else {
			if (x > x0) x = x0;
		}
	}


public:
	Var0(T _x, T _x0 = T{},T speed = T{1})
		: x{_x}
		, x0{_x0}
		, m_speed{speed}
	{
		m_speed = m_speed < T{} ? -m_speed : m_speed;
		if (x > x0) {
			m_speed = -m_speed;
			x_state = true;
		}
		else x_state = false;
	}

	operator T () { update(); return x; }

};

template<typename T>
class Var_ {
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");
	T x;
	T x0;
	T m_speed;
	T m_limit = std::numeric_limits<T>::max();

	void update() {
		x += m_speed;

		if (x >= m_limit) x = x0;
	}

public:
	Var_() : x{}, x0{}, m_speed { T(1) } {}
	Var_(T _x) : x{_x} , x0{ _x }, m_speed{ T(1) } {}
	Var_(T _x, T speed) : x{ _x }, x0{ _x }, m_speed{ speed } {}

	void Speed(T speed) { m_speed = speed; }
	T    Speed()  const { return m_speed; }

	void SetLimit(T limit) { m_limit = limit; }

	operator T () { update(); return x; }

	template<typename U>
	U as() {
		static_assert(std::is_arithmetic<U>::value, "type should be arithmetic");
		update();
		return static_cast<U>(x); 
	}

};


template<typename T>
class _Var_ {
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");
	T x;
	T last_x;
	T m_speed;
	T m_max;
	T m_min;
	T d_acc;
	bool enable_acceleration{ false };

	void update() {
		last_x = x;

		if (enable_acceleration) updateSpeed();

		x += m_speed;
		if (x > m_max) {
			m_speed = -m_speed;
			x = m_max;
			return;
		}

		if (x < m_min) {
			m_speed = -m_speed;
			x = m_min;
			return;
		}

		if (last_x == x)
		{
			std::cout << " x not changed do something\n";
			return;
		}
	}

	void updateSpeed() {
		if (m_speed < 0) {
			m_speed += d_acc;
		}
		else {
			m_speed -= d_acc;
		}
	}

public:
	_Var_() : x{}, last_x{}, m_speed{ T(1) }, m_max{ T(100) }, m_min{ T(0) } {}

	_Var_(T _x) : x{ _x }, last_x{}, m_speed{ T(1) }, m_max{ T(100) }, m_min{ T(0) } {}

	_Var_(T _x, T min, T max, T speed = T(1)) 
		:x{ _x }
		, last_x{}
		, m_speed{ speed }
		, m_max{ max }
		, m_min{ min }
	{
		d_acc =0.5f * (m_speed * m_speed) / (m_max - m_min);
	}

	void Speed(T speed) { m_speed = speed; }
	T    Speed()  const { return m_speed;  }

	void max(T _max) { m_max = _max; }
	T max() const { return m_max; }

	void min(T _min) { m_min = _min; }
	T min() const { return m_min; }

	operator T () { update(); return x; }

	template<typename U>
	U as() {
		static_assert(std::is_arithmetic<U>::value, "type should be arithmetic");
		update();
		return static_cast<U>(x);
	}

};

template<typename T>
class _Varbool_ {
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");
	T x;
	T last_x;
	T m_speed;
	T m_max;
	T m_min;
	bool x_stat;

	void update() {
		//x_stat = false;
		last_x = x;
		x += m_speed;
		if (x > m_max) {
			m_speed = -m_speed;
			x = m_max;
			x_stat = true;
			return;
		}

		if (x < m_min) {
			m_speed = -m_speed;
			x = m_min;
			x_stat = false;
			return;
		}

		if (last_x == x)
		{
			std::cout << " x not changed do something\n";
			return;
		}
	}

public:
	_Varbool_() : x{}, last_x{}, m_speed{ T(1) }, m_max{ T(100) }, m_min{ T(0) }, x_stat{ false } {}

	_Varbool_(T _x) : x{ _x }, last_x{}, m_speed{ T(1) }, m_max{ T(100) }, m_min{ T(0) }, x_stat{ false } {}

	_Varbool_(T _x, T min, T max, T speed = T(1))
		:x{ _x } // check if x is < min or > max?
		, last_x{}
		, m_speed{ speed }
		, m_max{ max }
		, m_min{ min }
		, x_stat{ false }
	{}


	void Speed(T speed) { m_speed = speed; }
	T    Speed()  const { return m_speed; }

	void max(T _max) { m_max = _max; }
	T max() const { return m_max; }

	void min(T _min) { m_min = _min; }
	T min() const { return m_min; }

	operator bool () { update(); return x_stat; }


};



using namespace std::chrono;

template<typename T>
class Var_t {
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");

	duration<float>            m_duration;
	steady_clock::time_point   tp1 ;
	duration<float>            elapsed_time{};

	T x0;
	T m_limit;
	float x;
	float m_speed;

	void update() {
		elapsed_time = steady_clock::now() - tp1;

		if (elapsed_time > m_duration) {
			x += m_speed;
			tp1 = steady_clock::now();
		};

		if (x > float(m_limit)) x = float(x0);
	}

public:
	Var_t(T x, T x_max, float _speed = 1.f, milliseconds duration = 1s)
		: x0{x}
		, m_limit{x_max}
		, x{float(x)}
		, m_speed {_speed}
		, m_duration{duration}
	//	, tp1{steady_clock::now()}
	{
		tp1 = steady_clock::now();
	}

	void setDuration(const milliseconds& duration) { m_duration = duration; }

	operator T () { update(); return static_cast<T>(x); }
};
