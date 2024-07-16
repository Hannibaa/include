#pragma once
#include<iostream>
#include<vector>

using namespace std;

int removeElement(vector<int>& v, int val)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == val)
		{
			v.erase(v.begin() + i); i--;
		};
	}

	return v.size();
}

template<typename Container, typename T = typename Container::value_type, typename Condition>
size_t removeElement(Container& container, const T& value, 
                     Condition condition = [](const T& x, const T& y){return x == y;} )
{
	
	for (auto it = container.begin(); it != container.end();){
		if ( condition(*it,value) ){
			it = container.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void printv(vector<int> v)
{
	cout << "vector : ";
	for (auto& a : v) cout << a << " ";
	cout << endl;
}
