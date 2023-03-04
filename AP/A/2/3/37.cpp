#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROW_NO = 7;
const int COL_NO = 7;

typedef vector<vector<char>> Board;

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

const Board END_POSITION =
    {{'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
     {'O', 'O', 'O', 'N', 'O', 'O', 'O'},
     {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
     {'X', 'X', 'O', 'O', 'O', 'X', 'X'}};

const vec MOVES[POSSIBLE_MOVES] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int number_of_N(const Board &disc)
{
    int N_counter = 0;
    for (int i = 0; i < ROW_NO; i++)
        for (int j = 0; j < COL_NO; j++)
            if (disc[i][j] == 'N')
                N_counter++;

    return N_counter;
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

bool check_way(int move, Board &disc, vector<moves> &steps, vec index);

bool find_way(Board &disc, vector<moves> &steps)
{
    if (disc == END_POSITION)
        return true;
    if (number_of_N(disc) == 1)
        return false;
    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
        {
            if (disc[i][j] == 'X' || disc[i][j] == 'O')
                continue;

            for (int move = 0; move < POSSIBLE_MOVES; move++)
            {
                if (check_way(move, disc, steps, {i, j}))
                    return true;
            }
        }
    }
    return false;
}

bool check_way(int move, Board &disc, vector<moves> &steps, vec index)
{
    int new_row, new_col, passed_row, passed_col;

    new_row = index.row_no + 2 * MOVES[move].row_no;
    passed_row = index.row_no + MOVES[move].row_no;

    new_col = index.col_no + 2 * MOVES[move].col_no;
    passed_col = index.col_no + MOVES[move].col_no;

    if (is_not_possible(new_row, new_col))
        return false;

    if (disc[new_row][new_col] == 'O' &&
        disc[passed_row][passed_col] == 'N')
    {
        disc[index.row_no][index.col_no] = 'O';
        disc[new_row][new_col] = 'N';
        disc[passed_row][passed_col] = 'O';
        steps.push_back({DIRECTIONS[move], {index.row_no, index.col_no}});

        if (find_way(disc, steps))
            return true;
        disc[index.row_no][index.col_no] = 'N';
        disc[new_row][new_col] = 'O';
        disc[passed_row][passed_col] = 'N';
        steps.pop_back();
    }
    return false;
}

int main()
{
    Board disc(ROW_NO, vector<char>(COL_NO));

    for (int i = 0; i < ROW_NO; i++)
    {
        for (int j = 0; j < COL_NO; j++)
            disc[i][j] = cin.get();

        cin.get();
    }
    vector<moves> steps;
    if (find_way(disc, steps))
        for (moves step : steps)
            cout << (char)(step.coordinate.row_no + 65) << step.coordinate.col_no + 1 << 
            ' ' << step.direction << endl;

    else
        cout << "Loser" << endl;
    return 0;
}