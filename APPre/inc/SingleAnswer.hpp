#ifndef _SINGLE_ANSWER_
#define _SINGLE_ANSWER_

#include "Query.hpp"

class SingleAnswer : public Query
{
private:
    vector<string> choices;
    string answer;

public:
    SingleAnswer(const QueryInfo &query_info);
    State is_answer_correct(const vector<string> &submitted_answers);
    void print_query();
    vector<string> get_answer();
};

#endif
