#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace Vec {

class Vector :public vector<int>
{
	string m_Name ="";
public:
	using vector<int>::vector;

	void push_front(int n){
		push_back(0);
		for (int i = size() - 1; i > 0; i--)
			at(i) = at(i - 1);
		at(0) = n;
	}

	void print() {
		cout << "Vector " << m_Name <<" = ";
		for (int i = 0; i < size(); i++) cout << at(i) << " ";
		cout << endl;
	}

	void setName(const string name) { m_Name = name; }

};

vector<int> numberBase(int n, int k)
{
	
	int b = n;
	int N;
	int i = 0;
	vector<int> a;
	if (n == 0) {
		a.push_back(0);
		return a;
	}
	while (b != 0)
	{
		N = b % k;
		a.push_back(N);
		b = (b - N) / k;
		i++;
	}
	return a;
}

int sumBase(int n, int k)
{
	int b = n;
	int N;
	int i = 0;
	int sum = 0;

	while (b != 0)
	{
		N = b % k;
		sum += N;
		b = (b - N) / k;
		i++;
	}

	return sum;
}
}