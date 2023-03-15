#include <iostream>
using namespace std;
const int MAX =50;
long long pow(int n, int k){
    if(k < 1)
    return 1;
    return n * pow(n,k-1);
}
long long factorial(int n){
    long long sum = 1;
    for (int i = 1; i<= n ;i++)
        sum *= i;
    return sum;
}
int main(){
    int cnt = 1;
    for(int n = 1; n<MAX;n++){
        for(int k = 1; k <MAX ; k++){
            if (factorial(n-1) == pow(n, k)-1)
            {cout <<cnt << " : for n = " <<n<< " and k = " << k << endl;
            cnt ++;}
        }
    }
    // cout << pow(6,3);
    return 0;
}