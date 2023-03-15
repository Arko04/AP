#include <vector>

#include<iostream>
using namespace std;
int main(){
    vector<vector<int> > w(3,{1,2});
    // vector<vector<int> > v(3,w);
    cout << w[0][0]<<endl;
    cout << w[1][1]<<endl;
    cout << w[2][0]<<endl;
}