#pragma once
#include <vector>
#include <array>
#include <iterator>
#include <type_traits>

template<typename iT, class BinaryCondition>
void Check2Obj_satisfy_Condition(iT first, iT last,BinaryCondition condition) {
	using ttype = typename iT::value_type;
	using type = typename std::iterator_traits<iT>::value_type;
	static_assert(std::is_arithmetic<type>::value, "Should be arithmetic type");
	//static_assert(std::is_function<BinaryCondition>::value, "Condition should be function");
	//static_assert(std::is_same<bool(*)(type, type), BinaryCondition>::value ||
	//	std::is_same<bool(type,type), BinaryCondition>::value ,
	//	"Condition should function of type bool()(type,type)");

	for (; first != last; ++first)
		for(auto f = (++first)--; f != last ; ++f)
		if ( condition(*first, *f))
		std::cout << *first << " " << *f << '\n';

}


template<typename T>
std::pair<unsigned int, unsigned int> 
Check2Obj_satisfy_Condition(T* a,size_t Size, T target) {

	static_assert(std::is_arithmetic<T>::value, "Should be an arithmetic type");

	std::pair<unsigned int, unsigned int> index_pair{};

	for (int i = 0; i < Size; i++)
	{
		for (int j = i + 1; j < Size; j++)
		{
			if (a[i] + a[j] == target) return std::make_pair(i, j);
		}
	}
	std::cout << "No result match target " << target << " \n";
	return std::make_pair(-1, -1);

}


template<typename T, template<typename ...> class Container = std::vector >
std::pair<unsigned int, unsigned int> Check2Obj_satisfy_Condition(Container<T> container, T target)
{
	static_assert(std::is_arithmetic<T>::value, "Should be arithmetic type");

	std::pair<unsigned int, unsigned int> index_pair{};

	for (int i = 0; i < container.size() ; i++)
	{
		for (int j = i + 1; j < container.size(); j++)
		{
			if (container[i] + container[j] == target) return std::make_pair(i,j);
		}
	}
	std::cout << "No result match target " << target << " \n";
	return std::make_pair(-1, -1);
}

template<typename T, typename Array>
std::pair<unsigned int, unsigned int> 
Check2Obj_satisfy_Condition(Array array, T target)
{
	static_assert(std::is_arithmetic<T>::value, "Should be arithmetic type");
	static_assert(std::is_same<std::array<T,array.size()>, Array>::value, "Should be array type");

	std::pair<unsigned int, unsigned int> Pair{};

	for (int i = 0; i < array.size(); i++)
	{
		for (int j = i + 1; j < array.size(); j++)
		{
			if (array[i] + array[j] == target) return std::make_pair(i, j);
		}
	}
	std::cout << "No result match target " << target << " \n";
	return std::make_pair(-1, -1);
}
