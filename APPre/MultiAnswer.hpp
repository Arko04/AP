#ifndef _MUL_ANSWER_
#define  _MUL_ANSWER_

#include "Query.hpp"
class MultiAnswer : public Query
{
    private:
        vector<string> choices;
        vector<string> answers;
    public:
    MultiAnswer(QueryInfo query_info);
    void print_query();
    State is_answer_correct(const vector<string> submitted_answers);
    vector<string> get_answer();
    // void print_more_info();
};

#endif