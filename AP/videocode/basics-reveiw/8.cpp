#include <iostream>
#include <vector>
using namespace std;
int most_frequent(vector<int> numbers);
int main()
{
    vector<int> numbers;
    int temp_num;
    while (cin >> temp_num)
        numbers.push_back(temp_num);
    cout<<most_frequent(numbers);
    return 0;
}
int most_frequent(vector<int> numbers){
    int cnt;
    int max = 0;
    int num;

    for (int i= 0;i<numbers.size();i++)
    {
        cnt = 0;
        for (int j = 0;j<numbers.size();j++){
            if(numbers[i] == numbers[j]){
                cnt++;
            }
        }
        if (cnt>max)
        {
            max  = cnt;
            num = numbers[i];
        }
    }
    return num;
}