#include "../inc/QuizInterface.hpp"
#include "../inc/Const.hpp"
#include "../inc/Utility.hpp"

int main(int argc, char *argv[])
{
    const string inp_file = argv[FILE_NAME_INDEX];
    QuizInterface quiz_interface(inp_file);
    quiz_interface.handle_input();
    return 0;
}