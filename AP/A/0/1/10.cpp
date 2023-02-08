#include <iostream>
using namespace std;
int main()
{
    int lines, maxTime, maxPeriod, noPeriods, sumOfTime = 0, start, end, period;
    cin >> lines;
    int flag[lines];
    for (int i = 0; i < lines; i++)
    {
        flag[i] = 1;
        cin >> maxTime >> maxPeriod >> noPeriods;
        for (int j = 0; j < noPeriods; j++)
        {
            cin >> start >> end;
            
            period = end - start;
            if (maxTime < (sumOfTime += period) || maxPeriod < period || period < 0)
            {
                flag[i] = 0;
            }
        }
        sumOfTime = 0;
    }
    for(int i = 0; i<lines; i++)
    {
        cout << flag[i];
    }
    cout << '\n';
    return 0;
}