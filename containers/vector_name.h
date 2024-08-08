#pragma once
#include <iostream>
#include <vector>

using namespace std;


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