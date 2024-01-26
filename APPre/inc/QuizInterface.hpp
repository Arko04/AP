#ifndef _QUIZ_INTERFACE_
#define _QUIZ_INTERFACE_

#include <memory>
#include "QuizMaker.hpp"
#include "Submit.hpp"

class QuizInterface
{
private:
    shared_ptr<QuizMaker> quiz;
    shared_ptr<Submit> submit;

    void print_correct_answer();
    void print_wrong_answer(const vector<string> &answers, const vector<string> &submitted_answers);
    void print_no_answer(const vector<string> &answers);
    void print_answers(const vector<string> &answers);
    void print_submitted_answers(const vector<string> &submitted_answers);

public:
    QuizInterface(const string &inp_file);
    void get_answer(bool &finished);
    void handle_input();
    void finish_exam();
    State submit_answer(const vector<string> &tokens);
};

#endif