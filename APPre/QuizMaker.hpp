#ifndef _QUIZ_MAKER_
#define _QUIZ_MAKER_

#include "Query.hpp"
#include "Submit.hpp"

class QuizMaker
{
private:
    vector <shared_ptr<Query> > queries;
public:
    QuizMaker(string file_name);
    int get_quiz_no();
    vector<string> get_answer(const int query_index);
    State is_answer_correct(const int query_index, vector<string> submitted_answer);
    // void print_more_info(const int query_index);
};

#endif

