// quera, icpc, Q5
#include <iostream>
using namespace std;
int main()
{
    int testcase, i, j, flag = 2, k, s, status;
    char c;
    cin >> testcase;
    int group[testcase], result[testcase];
    for (i = 0; i < testcase; i++)
    {
        cin >> group[i];
        getchar(); // why is that;
        int num[group[i]];
        for (j = 0; j < group[i]; j++)
        {
            c = getchar();
            if (c == 'U')

            {
                num[j] = 0;
            }
            else
            {
                num[j] = 1;
            }
        }
        result[i] = 0;
        for (k = 1; k <= group[i] / 2; k++)
        {
            flag = 2;
            status = 0;
            for (j = 0; j < group[i];)
            {
                for (s = 0; s < k && group[i] > j + s; s++)
                {
                    if (flag == num[j + s])
                    {
                        break;
                    }
                }
                if (s == k)
                {
                    flag = num[j];
                    status += k;
                    j += k;
                }
                else
                {
                    j++;
                }
            }
            status = (status / (2 * k)) * 2 * k;
            if (status > result[i])
            {
                result[i] = status;
            }
        }
    }
    for (i = 0; i < testcase; i++)
    {
        cout << result[i] << '\n';
    }
    return 0;
}
// ./a.out < 1.txt