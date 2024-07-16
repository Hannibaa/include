#pragma once

template<typename...T> class Tuples;

template<> class Tuples<> { };

template<typename T0, typename...TN>
class Tuples<T0, TN...> : public Tuples<TN...>
{
public:
	T0 value;
};
