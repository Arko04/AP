#include <iostream>
using namespace std;

void f(int x, int &y)
{
    int i = 5;
    x = i + 1;
    y = 18;
}
int main()
{
    int a = 10;
    int b = 11;

    const int& c = a+1;

    f(a, a+1);
    cout << a << b;
}