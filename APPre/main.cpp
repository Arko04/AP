#include <iostream>
#include "QuizInterface.hpp"
#include "Const.hpp"
#include "Utility.hpp" ///////////
using namespace std;
int main(int argc, char *argv[])
{
    // vector <string> hi = Utility::split_by("whatw 1 3", ' ');
    // cout << Utility::is_integer(hi[2])<<endl;
    const string inp_file = argv[FILE_NAME_INDEX];
    QuizInterface quiz_interface(inp_file);
    quiz_interface.handle_input();
    return 0;
}