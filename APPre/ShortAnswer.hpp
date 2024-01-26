#ifndef _SHORT_ANSWER_
#define _SHORT_ANSWER_

#include "Query.hpp"

class ShortAnswer : public Query
{
private:
    string answer;

public:
    ShortAnswer(const QueryInfo &query_info);
    State is_answer_correct(const vector<string> &submitted_answers);
    void print_query();
    vector<string> get_answer();
};

#endif