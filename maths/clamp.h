#pragma once

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return v < lo ? lo : hi < v ? hi : v;
}

template<typename T, T lo, T hi>
void clamp(T& x, const T& lo_value, const T& hi_value) {

	if (x < lo_value) x = lo;
	if (x > hi_value) x = hi;

}