#include <iostream>
using namespace std;
void reverse_number(int n, int &sum)
{
    if (n == 0)
        return;
    sum = sum * 10 + n % 10;
    n /= 10;
    reverse_number(n, sum);
}
int main()
{
    int n, sum = 0;
    cin >> n;
    reverse_number(n, sum);
    cout << sum << endl;
    return 0;
}