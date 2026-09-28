#include <iostream>

using namespace std;

int mouse_ways(int matrix_size, int row = 0, int col = 0)
{
    int way_count = 0;
    if (col == matrix_size)
        return 1;
    if (row == col)
        return mouse_ways(matrix_size, row, col + 1);
        
    way_count += mouse_ways(matrix_size, row + 1, col) +
                   mouse_ways(matrix_size, row, col + 1);
    return way_count;
}

int main()
{
    int matrix_size, ways_count;
    cin >> matrix_size;
    ways_count = mouse_ways(matrix_size);
    cout << ways_count << endl;
    exit(EXIT_SUCCESS);
}