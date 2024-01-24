#include "Submit.hpp"
#include "Const.hpp"
Submit::Submit(const int query_no)
{
    states = vector<State>(query_no, no_answer);
    submitted_answers = vector<vector<string>>(query_no, vector<string>());
}

void Submit::submit_answer(const int query_index, const State state, const vector<string> submitted_answer)
{
    submitted_answers[query_index - 1] = submitted_answer;
    if (states[query_index - 1] == no_answer)
    {
        states[query_index - 1] = state;
    }
    else
    {
        throw exception();
    }
}

State Submit::get_state(const int query_index)
{
    return states[query_index - 1];
}

void Submit::print_more_info(const int query_index)
{
    cout << YOUR_ANSWER;
    for (int i = 0; i < submitted_answers[query_index - 1].size(); i++)
    {
        cout << submitted_answers[query_index - 1][i] << SPACE;
    }
    cout << endl;
}