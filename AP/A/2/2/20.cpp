#include <iostream>

using namespace std;

typedef struct vec
{
    int x;
    int y;
} vec;

int count_mouse_ways(int matrix_number, int x = 0 ,int y = 0)
{
    // if (x == matrix_number && y == matrix_number)
    // {
    //     return 1;
    // }
        int way_counter = 0;
    if (y == matrix_number){
        return 1;
    }
    else if (x == y)
        return count_mouse_ways(matrix_number, x, y+1);
    else
    {
        way_counter += count_mouse_ways(matrix_number, x+1, y) +
                       count_mouse_ways(matrix_number, x, y+1);
        return way_counter;
    }
}
int main()
{
    int matrix_number;
    cin >> matrix_number;
    int ways = count_mouse_ways(matrix_number);
    cout << ways << endl;
    return 0;
}