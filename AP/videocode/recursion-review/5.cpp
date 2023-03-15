#include <iostream>
using namespace std;
int not_recurcive_sum(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int recurcive_sum(int n){
    if (n == 0)
        return 0;
    return n%10 + recurcive_sum(n/10);
}
int main()
{
    int n;
    cin >> n;
    cout << not_recurcive_sum(n)<<endl;
    cout << recurcive_sum(n)<<endl;

}