#pragma once

template<typename T>
T&& declval_() noexcept;

template<typename T>
const T declconst_(T x = T{}) noexcept;

template<typename T, template<typename T> class U  >
class X {

	U<T> M;
	U<U<T>> Z;

public:
	
	int operator()() { return 12; }
};