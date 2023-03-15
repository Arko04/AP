#include <iostream>
using namespace std;
int binary(int n){
    if (n <= 1)
    return n;
    return (n%2) + 10 *binary(n/2);
}
int main(){
    int n;
    cin >> n;
    int sum = binary(n);
    cout << sum<< endl;
    return 0;
}