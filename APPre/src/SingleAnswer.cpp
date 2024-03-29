#include "../inc/SingleAnswer.hpp"
#include "../inc/Const.hpp"
#include "../inc/Utility.hpp"
#include "../inc/Exception.hpp"

SingleAnswer::SingleAnswer(const QueryInfo &query_info) : Query(query_info)
{
    choices = query_info.choices;
    answer = query_info.answers[ANS_INDEX];
}

void SingleAnswer::print_query()
{
    Query::print_query();
    for (int i = 0; i < choices.size(); i++)
    {
        cout << choices[i] << endl;
    }
    cout << answer << endl;
}

State SingleAnswer::is_answer_correct(const vector<string> &submitted_answers)
{
    if (submitted_answers.size() < NUM_OF_SINGLE_ANSWER)
    {
        throw NoInput(NO_INPUT_ANSWER);
    }
    if (submitted_answers.size() > NUM_OF_SINGLE_ANSWER)
    {
        throw MultipleAnswer(MULTI_ANSWER_FOR_SINGLE_ANSWER);
    }
    if (!Utility::is_integer(submitted_answers[ANS_INDEX]))
    {
        throw InvalidInput(ANSWER_INDEX_IS_NOT_INTEGER);
    }
    else if (stoi(submitted_answers[ANS_INDEX]) > choices.size() || stoi(submitted_answers[ANS_INDEX]) < 1)
    {
        throw OutOfChoices(OUT_OF_CHOICES);
    }
    return (vector<string>(1, answer) == submitted_answers) ? correct : wrong;
}

vector<string> SingleAnswer::get_answer()
{
    return vector<string>({answer});
}