#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Move_details{
    int cur_f, cur_s, move_num;
};

const char num_to_ch[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

const string move_name[4] = {"LEFT", "UP", "RIGHT", "DOWN"};
const int   double_jump_f[4] = { 0, -2,  0, +2},                  // f as in first dimension and s as in second dimension
            double_jump_s[4] = {-2,  0, +2,  0},
            neighbour_f[4] =   { 0, -1,  0, +1},
            neighbour_s[4] =   {-1,  0, +1,  0};

bool Is_loc_O(char game_map[7][7], int f, int s){
    if (f < 0 or s < 0 or f >= 7 or s >= 7)
        return false;
    if (game_map[f][s] != 'O')
        return false;
    return true;
}

bool Is_loc_N(char game_map[7][7], int f, int s){
    if (f < 0 or s < 0 or f >= 7 or s >= 7)
        return false;
    if (game_map[f][s] != 'N')
        return false;
    return true;
}

bool Is_move_possible(char game_map[7][7], int f, int s, int move_number){
    if (Is_loc_N(game_map, f + neighbour_f[move_number], s + neighbour_s[move_number]) == false)
        return false;
    if (Is_loc_O(game_map, f + double_jump_f[move_number], s + double_jump_s[move_number]) == false)
        return false;
    return true;
}

int Count_of_N(char game_map[7][7]){
    int cnt = 0;
    for (int i = 0; i < 7; ++i){
        for (int j = 0; j < 7; ++j){
            if (game_map[i][j] == 'N')
                ++cnt;
        }
    }
    return cnt;
}


int main(int argc, char const *argv[])
{

	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */

    if (test_out.good()){
        string real_ans, user_ans;
        test_out >> real_ans;
        if (user_ans == real_ans)
            return 1;
        return 0;
    }

    char game_map[7][7];
    string line;
    int junk = 0;
    while (getline(test_in, line)){
        for (int i = 0; i < 7; ++i)
            game_map[junk][i] = line[i];
        ++junk;
    }

    while (getline(user_out, line)){
        int cur_f = line[0] - 'A', cur_s = line[1] - '1', move_n = -1;
        if ((int)line.size() == 7 and line.substr(3) == "LEFT")
            move_n = 0;
        if ((int)line.size() == 5 and line.substr(3) == "UP")
            move_n = 1;
        if ((int)line.size() == 8 and line.substr(3) == "RIGHT")
            move_n = 2;
        if ((int)line.size() == 7 and line.substr(3) == "DOWN")
            move_n = 3;
        
        if (move_n == -1)
            return 1;
        if (Is_loc_N(game_map, cur_f, cur_s) == false)
            return 1;
        
        if (Is_move_possible(game_map, cur_f, cur_s, move_n) == false)
            return 1;
        
        game_map[cur_f][cur_s] = 'O';
        game_map[cur_f + neighbour_f[move_n]][cur_s + neighbour_s[move_n]] = 'O';
        game_map[cur_f + double_jump_f[move_n]][cur_s + double_jump_s[move_n]] = 'N';
    }

    if (Count_of_N(game_map) == 1 and game_map[3][3] == 'N')
        return 0;
    return 1;

}