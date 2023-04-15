#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_vector_reverse(vector<int> v, int from = 0) {
	if (from >= v.size())
		return;
	print_vector_reverse(v, from + 1);
	cout << v[from] << ' ';
}

void print_vector(vector<int>& v, int from = 0) {
	if (from >= v.size())
		return;
	cout << v[from] << ' ';
	print_vector(v, from + 1);
}

void test_big_vector() {
	vector<int> v(5200000);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;
	print_vector(v);
}

int find_first(string s, char c) {
	if (s == "")
		return -1;
	if (s[0] == c)
		return 0;
	int index_in_tail = find_first(s.substr(1), c);	
	if (index_in_tail == -1)
		return -1;
	else
		return 1 + index_in_tail;
}

string merge(string s1, string s2) {
	if (s1 == "")
		return s2;
	if (s2 == "")
		return s1;
	if (s1[0] < s2[0])
		return s1[0] + merge(s1.substr(1), s2);
	else
		return s2[0] + merge(s1, s2.substr(1));
}

int main() {
	cout << merge("aadtx", "bccuyz") << endl;
}