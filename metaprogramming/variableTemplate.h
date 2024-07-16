#pragma once

template<typename T>
constexpr T Pi = (T) (3.1415);

template<typename T>
T y;

template<>
int y<char>;

template<typename T>
T z;
