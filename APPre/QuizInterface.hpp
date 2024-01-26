#ifndef _QUIZ_INTERFACE_
#define _QUIZ_INTERFACE_

#include "QuizMaker.hpp"
#include "Submit.hpp"

class QuizInterface
{
    private:
        shared_ptr<QuizMaker> quiz;
        shared_ptr<Submit> submit;

        void print_correct_answer();
        void print_wrong_answer(const vector<string> answers, const vector<string> submitted_answers);
        void print_no_answer(const vector<string> answers);
        void print_answers(vector<string> answers);
        void print_submitted_answers(vector<string> submitted_answers);
    public:
        QuizInterface(string inp_file);
        void get_answer(bool &finished);
        void handle_input();
        State submit_answer(vector<string> tokens);
        void finish_exam();
};

#endif