#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROW_NO = 7;
const int COL_NO = 7;

vector<vector<char> > get_board();

void print_board(vector< vector<char> >& board);

int main()
{
    vector<vector<char> > board = get_board();
    print_board(board);
    
    return 0;
}

vector<vector<char> > get_board()
{
    vector<vector<char> > board(ROW_NO, vector<char>(COL_NO));

    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            board[i][j] = cin.get();
        
        cin.get();
    }
    return board;
}

void print_board(const vector< vector<char> >& board){
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            cout << board[i][j];
        
        cout << endl;
    }
}