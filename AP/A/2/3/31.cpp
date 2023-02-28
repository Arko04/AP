#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROW_NO = 7;
const int COL_NO = 7;

char board[ROW_NO][COL_NO];

void get_board();

void print_board();

int main()
{
    get_board();
    print_board();
    return 0;
}

void get_board()
{

    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            board[i][j] = cin.get();
        
        cin.get();
    }
    return;
}

void print_board(){
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            cout << board[i][j];
        
        cout << endl;
    }
}