#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define EMPTY 'O'
#define FULL 'N'
#define NOT_POSSIBLE 'X'

const int ROW_NO = 7;
const int COL_NO = 7;

void print_board(vector<vector<char>> &board);

typedef struct vec
{
    int row_no;
    int col_no;
} vec;

const int POSSIBLE_MOVES = 4;
const string DIRECTIONS[POSSIBLE_MOVES] = {"DOWN", "RIGHT", "UP", "LEFT"};

typedef struct moves
{
    string direction;
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

const vec LEFT = {0, -1};
const vec RIGHT = {0, 1};
const vec UP = {-1, 0};
const vec DOWN = {1, 0};

const vec MOVES[POSSIBLE_MOVES] = {DOWN, RIGHT, UP, LEFT};

int number_of_N(const vector<vector<char>> &board)
{
    int n_counter = 0;
    for (int i = 0; i < ROW_NO; i++)
        for (int j = 0; j < COL_NO; j++)
            if (board[i][j] == 'N')
                n_counter++;

    return n_counter;
}

bool is_not_possible(int row_no, int col_no)
{
    if ((row_no < 2 && col_no < 2) ||
        (row_no > 4 && col_no > 4) ||
        (row_no < 2 && col_no > 4) ||
        (row_no > 4 && col_no < 2))
        return true;

    if (col_no < 0 ||
        row_no < 0 ||
        col_no > 6 ||
        row_no > 6)
        return true;

    return false;
}
bool find_way(vector<vector<char>> &board, vector<moves> &steps)
{
    if (board == END_POSITION)
        return true;
    if (number_of_N(board)== 1)
        return false;
    int new_row, new_col;
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
        {
            if (board[i][j] == 'X' || board[i][j] == 'O')
                continue;

            for (int move = 0; move < POSSIBLE_MOVES; move++)
            {
                new_row = i + 2 * MOVES[move].row_no;
                new_col = j + 2 * MOVES[move].col_no;
                if (is_not_possible(new_row, new_col))
                    continue;

                if (board[new_row][new_col] == 'O' &&
                    board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] == 'N')
                {
                    board[i][j] = 'O';
                    board[new_row][new_col] = 'N';
                    board[new_row - MOVES[move].row_no][new_col - MOVES[move].col_no] = 'O';
                    steps.push_back({DIRECTIONS[move], {i, j}});

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
        for (moves x : steps)
            cout << (char)(x.coordinate.row_no + 65) << x.coordinate.col_no + 1 << ' ' << x.direction << endl;

    else
        cout << "Loser" << endl;
    return 0;
}