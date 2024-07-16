#pragma once


template<class T, int N>
class Stack
{
private:

	T s[N];
	int l = 0; // last element pushed in stack

public:

	void push(const T& x)
	{
		s[l++] = x;
	}

	T& pop()
	{
		if (l == 0) { std::cout << "Empty stack\n"; return s[0]; }
		T x = s[l--];
		s[l + 1].~T();
		return x;
	}

	bool isEmpty () const
	{
		return l == 0;
	}

	int getlength() const { return l; }

};
