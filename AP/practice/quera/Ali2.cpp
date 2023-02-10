// ali's code
// shir to shir, quera, icpc
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int t;
    cin >> t;
    double a[t];
    double sum = 0;
    for (int i = 0; i < t; i++)
    {
        cin >> a[i];
    }
    for (int i = t - 1; i >= 0; i--)
    {
        double temp = a[i];
        a[i] = a[i] + sum / (i + 1);
        sum += temp;
    }
    for (int i = 0; i < t; i++)
    {
        printf("%.5f ", a[i]);
    }
    cout << endl;
    return 0;
}