#pragma once

template<int N>
constexpr int Factorial() {
	return N * Factorial<N - 1>();
}

template<>
constexpr int Factorial<0>() {
	return 1;
}
