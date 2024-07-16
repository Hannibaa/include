#pragma once


template<typename C>
typename C::value_type get_nth_element(const C& container, int N) {
	if (N > container.size()) { std::cout << "Error out of range\n"; }
	return container[N];
}


template<typename T>
T get_nth_element(T* array, int SizeArray, int N) {
	if (N > SizeArray) { std::cout << "Error out of range\n"; }
	return array[N];
}