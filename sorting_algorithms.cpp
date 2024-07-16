#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(int* a, int n_element)
{
	for (int i = 0; i < n_element; i++)
		cout << a[i] << "  ";
	cout << endl;
}

void printv(vector<int> a)
{
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << "  ";
	cout << endl;
}


/* FIRST IN ALL ALGORITHM STUDYED HERE WE USE INTEGER NUMBER AFTER USE GENERIC  */
//----------------------------------- FUNCTION 1 --------------------------------/
//                         BUBLLING MAX IN ARRAY TO RIGHT                       //
//           BUBLLING MAX DEPEND ON ORDER RELATION DEFINED BY 'R(X,Y)'          //
//                                 RETURN MAXIMUM                               //

int bubble_right(vector<int> a, bool (*r)(int, int) = [](int a, int b)->bool {return a > b; })
{
	int swap;
	// bubble max on right
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (r(a[i],a[i+1])) {
			swap = a[i];
			a[i] = a[i + 1];
			a[i + 1] = swap;
		}
	}
	printv(a);
	return a[a.size() - 1];

}

int bubble_left(vector<int> a, bool (*r)(int, int) = [](int a, int b)->bool {return a > b; })
{
	int swap;
	for (int i = a.size() - 1; i >= 1; i--)
	{
		if (r(a[i] , a[i - 1]))
		{
			swap = a[i];
			a[i] = a[i - 1];
			a[i - 1] = swap;
		}
	}
	printv(a);
	return a[0];

}

int bubble_sort(vector<int> a, bool (*r)(int, int) = [](int a, int b)->bool {return a < b; })
{
	int swap;
	for(int j = a.size()-1; j>1; j--)
	   for (int i = 0; i < j; i++)
	   {
		if (r(a[i], a[i + 1])) {
			swap = a[i];
			a[i] = a[i + 1];
			a[i + 1] = swap;
		}
	   }
	printv(a);

	return 0;
}

int indexOfMax(vector<int> a, bool (*r)(int, int) = [](int a, int b)->bool {return a > b; })
{
	int index = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (r(a[index] , a[i])) index = i;
	}
	return index;
}

void rank(vector<int> a, vector<int>& r)
{

}

int main()
{
	int a[] = { 22, 4, 22, 10, 4, 8, 6 };
	vector<int> v{ 20, 40, -22, 10,1,10, 28, 4, 80 };
	int n = 7;
	printv(v); 

	cout << indexOfMax(v) << endl;

	cin.get();
	return 0;
}

//cout << "bubble sort of vector v " << endl;
//cout << bubble_sort(v) << endl;
//printv(v);


//cout << bubble_right(v) << endl;
//cout << "Bubbling min to left absulot value " << endl;
//cout << bubble_left(v, [](int a, int b)->bool { return abs(a) < abs(b); }) << endl;
//cout << "Bubbling min to left " << endl;
//cout << bubble_left(v, [](int a, int b)->bool { return a < b; }) << endl;
//cout << "Bubbling min following order relation defining by function" << endl;
//cout << bubble_left(v, [](int a, int b)->bool { return !(a < b) || (cos(a) < cos(b)); }) << endl;
//cout << "Bubbling max to left  " << endl;
//cout << bubble_left(v, [](int a, int b)->bool { return a > b; }) << endl;
//cout << "Bubbling max to right" << endl;
//cout << bubble_right(v, [](int a, int b)->bool {return a > b; }) << endl;


//cout << bubble_max_right(a, 7) << endl;
//print(a, 7);
//int swap;
//// bubble max on right
//for (int i = 0; i < n-1; i++)
//{
//	if (a[i + 1] < a[i]) {
//		swap = a[i];
//		a[i] = a[i+1];
//		a[i + 1] = swap;
//	}
//}
//print(a, n);
//cout << endl;
//cout << bubble_max_right(v) << endl;
//printv(v);
