#include <iostream>
#include <vector>

using namespace std;
#define MAX 0
#define MIN 1

int min(int num1, int num2)
{
    return (num1 < num2) ? num1 : num2;
}

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

void traverse(vector<int> numbers, int num1 = 0, int index = 0, int condition = MAX)
{
    if (numbers.size() - 1 < index)
        return;

    int num2 = numbers.at(index);
    cout << num2 << ' ';
    
    if ((num1 == 0 && num2 == 0))
        return;

    else
    {
        if (condition == MAX)
        {
            index += max(num1, num2);
            condition = MIN;
        }
        else
        {
            index += min(num1, num2);
            condition = MAX;
        }
        traverse(numbers, num2, index, condition);
    }
}
int main()
{
    int number_count, num;
    cin >> number_count;
    vector<int> numbers(number_count);
    for (int i = 0; i < number_count; i++)
    {
        cin >> num;
        numbers.at(i) = num;
    }
    traverse(numbers);
    cout << endl;
    return 0;
}