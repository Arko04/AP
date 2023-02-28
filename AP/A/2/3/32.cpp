#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROW_NO = 7;
const int COL_NO = 7;

void print_board(vector<vector<char>> &board);

typedef struct vec
{
    int row_no;
    int col_no;
} vec;

typedef struct moves
{
    int direction;
    vec coordinate;
} moves;

const vector<vector<char>> END_POSITION =
    {{'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
     {'O', 'O', 'O', 'N', 'O', 'O', 'O'},
     {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'}};

// bool does_end(vector<vector<char>> board)
// {

//     if (board == END_POSITION)
//         return true;
//     return false;
// }
const int POSSIBLE_MOVES = 4;

const vec LEFT = {0, -1};
const vec RIGHT = {0, 1};
const vec UP = {-1, 0};
const vec DOWN = {1, 0};

const vec MOVES[POSSIBLE_MOVES] = {DOWN, RIGHT, UP, LEFT};

bool find_way(vector<vector<char>> board, vector<moves> &steps, vec square = {0, 0})
{
    if (board == END_POSITION)
        return true;
    int new_row, new_col;
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
        {
            if(board[i][j]== 'X' ||board[i][j]== 'O'){
                continue;
            }
            square = {i, j};
            for (int move = 0; move < POSSIBLE_MOVES; move++)
            {
                new_row = square.row_no + 2 * MOVES[move].row_no;
                new_col = square.col_no + 2 * MOVES[move].col_no;
                if (new_row < 2 || new_col < 2 || new_col > 4 || new_col > 4)
                    continue;

                if (board[new_row][new_col] == 'O' && board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] == 'N')
                {
                    board[new_row][new_col] = 'N';
                    board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] = 'O';
                    if (find_way(board, steps ,{0,0}))
                        return true;

                    board[new_row][new_col] = 'O';
                    board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] = 'N';
                }
            }
        }
    }
    return false;
}

int main()
{
    vector<vector<char>> board(ROW_NO, vector<char>(COL_NO));

    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            board[i][j] = cin.get();

        cin.get();
    }
    vector<moves> steps;
    if (find_way(board, steps))
    {
        // print steps function
        // cout << "WINNER" << endl;
    }
    else
    {
        cout << "Loser" << endl;
    }
    print_board(board);

    return 0;
}

void print_board(vector<vector<char>> &board)
{
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            cout << board[i][j];

        cout << endl;
    }
}