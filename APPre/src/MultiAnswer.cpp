#include "../inc/MultiAnswer.hpp"
#include "../inc/Const.hpp"
#include "../inc/Utility.hpp"
#include "../inc/Exception.hpp"

MultiAnswer::MultiAnswer(const QueryInfo &query_info) : Query(query_info)
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

State MultiAnswer::is_answer_correct(const vector<string> &submitted_answers)
{
    for (int i = 0; i < submitted_answers.size(); i++)
    {
        if (submitted_answers.size() < NUM_OF_SINGLE_ANSWER)
        {
            throw NoInput(NO_INPUT_ANSWER);
        }
        if (!Utility::is_integer(submitted_answers[i]))
        {
            throw InvalidInput(ANSWER_INDEX_IS_NOT_INTEGER);
        }
        else if (stoi(submitted_answers[i]) > choices.size() || stoi(submitted_answers[i]) < 1)
        {
            throw OutOfChoices(OUT_OF_CHOICES);
        }
    }
    return (answers == submitted_answers) ? correct : wrong;
}

vector<string> MultiAnswer::get_answer()
{
    return answers;
}