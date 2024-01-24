#include "ShortAnswer.hpp"
#include "Const.hpp"
ShortAnswer::ShortAnswer(QueryInfo query_info):Query(query_info)
{
    answer = query_info.answers[ANS_INDEX];
}

void ShortAnswer::print_query()
{
    Query::print_query();
    cout << answer << endl;
}

State ShortAnswer::is_answer_correct(const vector<string> submitted_answers)
{
     return (vector<string>(1, answer) == submitted_answers) ? correct : wrong;
}

void ShortAnswer::print_more_info()
{
    cout << CORRECT_ANSWER <<answer;
}