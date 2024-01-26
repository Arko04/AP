#include "../inc/ShortAnswer.hpp"
#include "../inc/Exception.hpp"
#include "../inc/Const.hpp"

ShortAnswer::ShortAnswer(const QueryInfo &query_info) : Query(query_info)
{
    answer = query_info.answers[ANS_INDEX];
}

void ShortAnswer::print_query()
{
    Query::print_query();
    cout << answer << endl;
}

State ShortAnswer::is_answer_correct(const vector<string> &submitted_answers)
{
    if (submitted_answers.size() < NUM_OF_SINGLE_ANSWER)
    {
        throw NoInput(NO_INPUT_ANSWER);
    }
    if (submitted_answers.size() > NUM_OF_SINGLE_ANSWER)
    {
        throw MultipleAnswer(MULTI_ANSWER_FOR_SHORT_ANSWER);
    }
    return (vector<string>(1, answer) == submitted_answers) ? correct : wrong;
}

vector<string> ShortAnswer::get_answer()
{
    return vector<string>({answer});
}