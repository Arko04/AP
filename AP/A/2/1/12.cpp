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

void traverse(vector<int>& numbers, int prev_num = 0, int cur_index = 0, int condition = MAX)
{
    if (numbers.size() - 1 < cur_index)
        return;
        
    int cur_num = numbers.at(cur_index);
    cout << cur_num << ' ';

    if ((prev_num == 0 && cur_num == 0))
        return;

    else
    {
        if (condition == MAX)
        {
            cur_index += max(prev_num, cur_num);
            condition = MIN;
        }
        else
        {
            cur_index += min(prev_num, cur_num);
            condition = MAX;
        }
        traverse(numbers, cur_num, cur_index, condition);
    }
}

vector<int> input_numbers()
{
    int number_count, num;
    cin >> number_count;

    vector<int> numbers(number_count);

    for (int i = 0; i < number_count; i++)
    {
        cin >> num;
        numbers.at(i) = num;
    }
    return numbers;
}

int main()
{
    vector<int> numbers = input_numbers();
    traverse(numbers);
    cout << endl;
    exit(EXIT_SUCCESS);
}