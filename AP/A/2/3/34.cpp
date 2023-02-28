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

const int POSSIBLE_MOVES = 4;

const vec LEFT = {0, -1};
const vec RIGHT = {0, 1};
const vec UP = {-1, 0};
const vec DOWN = {1, 0};

const vec MOVES[POSSIBLE_MOVES] = {DOWN, RIGHT, UP, LEFT};

int number_of_N(const vector<vector<char>> &board)
{
    int n_counter = 0;
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
        {
            if (board[i][j] == 'N')
                n_counter++;
        }
    }
    return n_counter;
}
bool find_way(vector<vector<char>> &board, vector<moves> &steps)
{
    if (board == END_POSITION)
        return true;
    int n_counter;
    if ((n_counter = number_of_N(board)) == 1)
        return false;
    int new_row, new_col;
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
        {
            if (board[i][j] == 'X' || board[i][j] == 'O')
            {
                continue;
            }

            for (int move = 0; move < POSSIBLE_MOVES; move++)
            {
                new_row = i + 2 * MOVES[move].row_no;
                new_col = j + 2 * MOVES[move].col_no;
                if ((new_row < 2 && new_col < 2) ||( new_row > 4 && new_col > 4 )|| (new_row < 2 && new_col > 4 )|| (new_row > 4 && new_col < 2))
                    continue;
                if (new_col < 0 || new_row < 0 || new_col > 6 || new_row > 6)
                    continue;

                if (board[new_row][new_col] == 'O' && board[i + MOVES[move].row_no][j+ MOVES[move].col_no] == 'N')
                {
                    board[i][j] = 'O';
                    board[new_row][new_col] = 'N';
                    board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] = 'O';
                    steps.push_back({move, {i, j}});

                    if (find_way(board, steps))
                        return true;
                    steps.pop_back();
                    board[i][j] = 'N';
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
        string action;
        for (moves x : steps)
        {
            switch (x.direction)
            {
            case 0:
                action = "DOWN";
                break;
            case 1:
                action = "RIGHT";
                break;
            case 2:
                action = "UP";
                break;
            case 3:
                action = "LEFT";
                break;
            }
            cout << (char)(x.coordinate.row_no + 65) << x.coordinate.col_no + 1 << ' ' << action << endl;
        }
    }
    else
        cout << "Loser" << endl;
    return 0;
}