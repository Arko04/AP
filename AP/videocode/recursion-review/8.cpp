#include <iostream>
#include <vector>
#include <string>

using namespace std;
int count_positive(vector<int>& numberList, int index)
{
    // for (int i = index; i < numberList.size(); i++)
    //     cout << numberList.at(i) << endl;
    // cout << '\n';
    // vector<int> newNumberList(numberList.begin()+1, numberList.end());
    if (index == numberList.size())
        return 0;
    int curr_num = numberList.at(index);
    if ( curr_num> 0)
        return (curr_num + count_positive(numberList, ++index));
    else
        return (count_positive(numberList, ++index));
}
int main()
{
    vector<int> numberList;
    int n;
    cin >> n;
    int number;
    for (int i = 0; i < n; i++)
    {
        cin >> number;
        numberList.push_back(number);
    }
    // cout << '\n';
    // for (int i = 0; i < n; i++)
    //     cout << numberList.at(i)<<endl;

    int positive_number = count_positive(numberList, 0);
    cout << positive_number << endl;
}