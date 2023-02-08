#include <iostream>
using namespace std;
int main()
{
    int lines, maxTime, maxPeriod, noPeriods, sumOfTime = 0, start, end, period, i, j;
    cin >> lines;
    int flag[lines], timePlus[lines], periodPlus[lines];
    for (i = 0; i < lines; i++)
    {
        flag[i] = 1;
        timePlus[i] = 0;
        periodPlus[i] = 0;
        cin >> maxTime >> maxPeriod >> noPeriods;
        for (j = 0; j < noPeriods; j++)
        {
            cin >> start >> end;

            period = end - start;
            if (maxTime < (sumOfTime += period) || maxPeriod < period || period < 0)
            {           
                flag[i] = 0;
                if (periodPlus[i] < period - maxPeriod)
                {
                    periodPlus[i] = period - maxPeriod;
                }
            }
        }
        if (maxTime < sumOfTime)
        {
            timePlus[i] = sumOfTime - maxTime;
        }
        sumOfTime = 0;
    }
    for (i = 0; i < lines; i++)
    {
        cout << timePlus[i] << ' ' << periodPlus[i] << '\n';
    }
    return 0;
}