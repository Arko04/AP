#include <iostream>
#include <ctime>
#include <vector>

using namespace std;
void bubble_sort_1(vector<int> v)
{

	for (int i = 0; i < v.size() - 1; i++)

		for (int j = 0; j < v.size() - i - 1; j++)

			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
}

void bubble_sort_2(vector<int> v)
{

	vector<int> w = v;

	for (int i = 0; i < w.size() - 1; i++)

		for (int j = 0; j < w.size() - i - 1; j++)

			if (w[j] > w[j + 1])
			{
				swap(w[j], w[j + 1]);
			}

	v = w;
}
int main()
{
	vector<int> v(5000);
	for (int i = 0; i < 5000; i++)
		v.at(i) = 5000-i;

	clock_t timer;

	timer = clock();
	bubble_sort_1(v);
	// cout << bubble_sort_1(v)<< endl;
	timer = clock() - timer;
	cout << "Version 1: " << 1000 * timer / CLOCKS_PER_SEC << "(ms)\t\t";

	timer = clock();
	bubble_sort_2(v);
	// cout << bubble_sort_2(v)<< endl;
	timer = clock() - timer;
	cout << "Version 2: " << 1000 * timer / CLOCKS_PER_SEC << "(ms)" << endl;

	return 0;
}
// why does the first function take more time than the second one?