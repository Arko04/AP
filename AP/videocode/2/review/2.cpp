#include <iostream>
// using namespace std;
typedef float inch;
int main(){
    inch number;
    std::cout << "Please enter the number in inch: ";
    std::cin >> number;
    float num = number/2.54;
    std::cout<< num<<std::endl;
    return 0;
}