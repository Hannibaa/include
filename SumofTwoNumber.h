#pragma once
#include <array>
#include <vector>
#include <map>
#include <iterator>
#include <type_traits>

template<typename T, size_t N>
void sum2Number_(std::array<T,N> a, T target) {
	static_assert(std::is_arithmetic<T>::value, "Arithmetic type required");
	T I = -1, J = -1;

	for (int i = 0; i < N; i++)
	{
		for(int j = i+1; j < N ; j++)
			if (a[i] + a[j] == target) { I = i; J = j; break; }
		if (I != -1 && J != -1) break;
	}

	std::cout << "I " << I << " ,J " << J << std::endl;
	std::cout << "element : " << a[I] << " , " << a[J] << std::endl;
}


//
//   We have problem for repetition value like { 1,1,3,5,7,1,3,3} for all possible target.
//
template<typename T>
std::vector<std::pair<int,int> >  
sum2Number(std::vector<T> v, T target, bool first_pair_only = true) {

	static_assert(std::is_arithmetic<T>::value, "type should be integer");

	std::vector<std::pair<int, int> > vpair{ };
	std::map<T, int> vmap;
	T a{};

	for (int i = 0; i < v.size(); i++)
	{
		a = target - v[i];
		if (! vmap.contains(a)) { vmap[v[i]] = i ; }
		else 
		{ 
			vpair.push_back(std::make_pair(vmap[a], i));
			vmap[v[i]] = i;
			if ( first_pair_only ) 	break;
		}
	}

	if (vpair.empty()) vpair.push_back({ 0,0 });
	return vpair;
}


//
template<typename T, size_t N>
void allPossibleSum(std::array<T, N> a) {
	static_assert(std::is_arithmetic<T>::value, "type should be mathematical number");
	int I = 0;
	for ( int i = 0 ; i < N ; i++)
		for (int j = i + 1; j < N; j++)
		{
			std::cout << "[ " << I++ << ", " << a[i] + a[j] << " ] ";
		}
}

//////////////////////////////////////////////////////////////////////////////////////////
//				ALL POSSIBLE SUM BETWEEN ELEMENT OF CONTAINER 							//
//////////////////////////////////////////////////////////////////////////////////////////

template<typename iT>
void AllPossibleSum(iT first, iT last)
{
	static_assert(std::is_arithmetic<typename std::iterator_traits<iT>::value_type>::value, 
		"type should be arithmetic");
	int I{};
	for (; first != last ; ++first )
		for (auto f = (++first)-- ; f != last ; ++f)
		{
			std::cout << "[ " << I++ << ", " << *first + *f << " ] ";
		}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//           GENERALIZATION OF SUM TWO NUMBER OVER ANY CONTAINER	O(n)				   //	
/////////////////////////////////////////////////////////////////////////////////////////////
//    We have problem for repetition value like{ 1,1,3,5,7,1,3,3 } for all possible target.

template<typename iter>
std::vector<std::pair<int,int>>
Sum2Number(iter first, iter last, typename std::iterator_traits<iter>::value_type target,
	                                                           bool first_pair_only = true)
{
	using type = typename std::iterator_traits<iter>::value_type;
	static_assert(std::is_arithmetic<type>::value, "Should be arithmetic type");

	std::vector<std::pair<int, int>> vpair{};
	std::map<type, int> map;
	type a{};
	int i{};
	for (; first != last; ++first, i++)
	{
		a = target - *first;
		if (!map.contains(a)) { map[*first] = i; }
		else
		{
			vpair.push_back(std::make_pair(map[a], i));
			map[*first] = i;
			if (first_pair_only) break;
		}
	}

	if (vpair.empty()) vpair.push_back({ 0,0 });
	return vpair;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//           GENERALIZATION OF SUM TWO NUMBER OVER ANY CONTAINER	O(n*n)				   //	
/////////////////////////////////////////////////////////////////////////////////////////////

template<typename iter>
std::vector<std::pair<int,int>> 
Sum2Number_(iter first, iter last, typename std::iterator_traits<iter>::value_type target, bool all_pair = false)
{
	using ttype = typename iter::value_type;
	using type = typename std::iterator_traits<iter>::value_type;
	static_assert(std::is_arithmetic<type>::value, "Should be arithmetic type");
	std::vector<std::pair<int, int>> vpair{};
	int i{}; int j{};
	for (; first != last; ++first , i++)
	{
		j = i + 1;
		for(iter f = (++first)-- ; f != last; ++f, j++)
			if (*first + *f == target) {
				vpair.push_back(std::make_pair( i,j ));
				if (!all_pair) goto _end;
			}
	}
_end:
	if (vpair.empty()) vpair.push_back({ 0,0 });

	return vpair;
}