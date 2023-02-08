// enter some numbers with semicolon between
// this code sorts the numbers in ascending order
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *numbers = NULL, temp, cnt = 0, status, flag = 1;
    while (flag)
    {
        // check if the user enters character
        status = scanf("%d", &temp);
        if (status)
        {
            cnt++; 
            if ((numbers = (int *)realloc(numbers, cnt * sizeof(int))) == NULL)
            {
                printf("Unable to allocate memory\n");
                exit(EXIT_FAILURE);
            }
            numbers[cnt - 1] = temp;
        }
        else
        {
            printf("don't allow to enter character\n");
            getchar();
            break;
        }
        char c = getchar();
        switch (c)
        {
	// user should enter semicolon between numbers 
        case ',':
            continue;
            break;
        default:
            flag--;
            break;
        }
    }
    for (int i = 1; i < cnt; i++)
    {
        if (numbers[i - 1] > numbers[i])
        {
            temp = numbers[i];
            numbers[i] = numbers[i - 1];
            numbers[i - 1] = temp;
            i = 0;
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", numbers[i]);
    }
    free(numbers);
    exit(EXIT_SUCCESS);
}


