#include <iostream>
using namespace std;
long power(int n, int k)
{
    if (k <= 0)
        return 1;

    return n * power(n, k - 1);
}
int main()
{
    int n ,k;
    cin >>n>>k;
    long sum = power(n, k);
    cout << sum << endl;
}