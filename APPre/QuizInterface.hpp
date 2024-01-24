#include "QuizMaker.hpp"
#include "Submit.hpp"
class QuizInterface
{
    private:
        shared_ptr<QuizMaker> quiz;
        shared_ptr<Submit> submit;
    public:
        QuizInterface(string inp_file);
        void get_answer();
        void handle_input();
        State submit_answer(vector<string> tokens);
        void finish_exam();
};