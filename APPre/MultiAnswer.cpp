#include "MultiAnswer.hpp"
#include "Const.hpp"
MultiAnswer::MultiAnswer(QueryInfo query_info) : Query(query_info)
{
    choices = query_info.choices;
    answers = query_info.answers;
}
void MultiAnswer::print_query()
{
    Query::print_query();
    for (int i = 0; i < choices.size(); i++)
    {
        cout << choices[i] << endl;
    }
    for (int i = 0; i < answers.size(); i++)
    {
        cout << answers[i] << SPACE;
    }
    cout << endl;
}

State MultiAnswer::is_answer_correct(const vector<string> submitted_answers)
{
    return (answers == submitted_answers) ? correct : wrong;
}

void MultiAnswer::print_more_info()
{
    cout << CORRECT_ANSWER;
    for (int i = 0 ; i < answers.size();i++)
    {
        cout << answers[i]<<SPACE;
    }
}