#include <iostream>
#include <vector>
using namespace std;
vector<int> most_frequent(vector<int> numbers);
int main()
{
    vector<int> numbers;
    int temp_num;
    while (cin >> temp_num)
        numbers.push_back(temp_num);
    vector<int> maxnumbers = most_frequent(numbers);
    for (int x : maxnumbers)
        cout << x << ' ';

    return 0;
}

vector<int> most_frequent(vector<int> numbers)
{
    vector<int> maxnumbers;
    int cnt, i, j, k;
    int max = 0;
    int vsize = numbers.size();
    for (i = 0; i < vsize; i++)
    {
        cnt = 0;
        for (j = 0; j < vsize; j++)
            if (numbers[i] == numbers[j])
                cnt++;
        if (cnt > max)
        {
            maxnumbers.clear();
            max = cnt;
        }
        if (cnt == max)
        {
            for (k = 0; k < maxnumbers.size(); k++)
                if (maxnumbers[k] == numbers[i])
                    break;
            if (k == maxnumbers.size())
                maxnumbers.push_back(numbers[i]);
        }
    }
    return maxnumbers;
}