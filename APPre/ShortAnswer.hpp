#include "Query.hpp"
class ShortAnswer : public Query
{
    private:
        string answer;
    public:
    ShortAnswer(QueryInfo query_info);
    void print_query();
    State is_answer_correct(const vector<string> submitted_answers);
    void print_more_info();
};