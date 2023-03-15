#include <iostream>
using namespace std;
#define MAX 100
int main(){
    int counter = 1;
    long long number, mazrab1, mazrab2;
    for(int m = 1; m < MAX; m++){
        for (int n = 1 ; n < MAX; n++){
            number = m*n - 1;
            mazrab1 = m*m*m +1;
            mazrab2 = n*n*n +1;
            if(mazrab1%number == 0 && mazrab2%number == 0){
                cout << counter<< " :"<<"for m = "<< m << " and n = "<< n << endl;
                counter++;
            }
        }
    }
    return 0 ;
}