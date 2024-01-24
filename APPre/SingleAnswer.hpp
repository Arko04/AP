#include "Query.hpp"
class SingleAnswer : public Query
{
    private:
        vector<string> choices;
        string answer;
    public:
    SingleAnswer(QueryInfo query_info);
    void print_query();
    State is_answer_correct(const vector<string> submitted_answers);
    void print_more_info();
};

