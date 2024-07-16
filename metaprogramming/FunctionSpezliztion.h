#pragma once


template<typename T> T max_value(); // only declaration

template<> constexpr int max_value<int>()   { return INT_MAX;  } 
template<> constexpr char max_value<char>() { return CHAR_MAX; }

int max_value2(int) { return INT_MAX; }
int max_value2(char) { return CHAR_MAX; }
