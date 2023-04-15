#include <iostream>
using namespace std;
int main()
{
    int a, b;
    cin >> a >> b;
    // if (a < b)
    //     swap(a, b);
    
    // for (int i = a; i > 0; i--)
    //     if (b % i == 0 && a % i == 0)
    //     {
    //         cout << i ;
    //         break;
    //     }
    cout <<(a<b?a:b) << endl;
    return 0;
}