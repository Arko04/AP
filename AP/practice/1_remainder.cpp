#include <iostream>
using namespace std;
#define MAX 19

int main()
{
    long long sum = 1;
    for (int i = 1; i < MAX; i++)
    {
        cout << "for " << i << " :" << (i * i) % MAX << endl;
        sum = sum * i;
        cout << "THE SUM IS : " << sum % MAX << endl;
    }

    return 0;
}