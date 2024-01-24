#include "SingleAnswer.hpp"
#include "Const.hpp"
#include <iostream>
using namespace std;
SingleAnswer::SingleAnswer(QueryInfo query_info) : Query(query_info)
{   
    choices = query_info.choices;
    answer = query_info.answers[ANS_INDEX];
}

void SingleAnswer::print_query()
{
    Query::print_query();
    for(int i = 0 ; i < choices.size(); i++)
    {
        cout << choices[i] << endl;
    }
    cout << answer << endl;
}

State SingleAnswer::is_answer_correct(const vector<string> submitted_answers)
{
    return (vector<string>(1, answer) == submitted_answers) ? correct : wrong;
}

void SingleAnswer::print_more_info()
{
    cout << CORRECT_ANSWER <<answer;
}