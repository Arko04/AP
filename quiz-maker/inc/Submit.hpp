#ifndef _SUBMIT_
#define _SUBMIT_

#include <iostream>
#include <vector>
using namespace std;

enum State
{
    correct,
    wrong,
    no_answer,
};

class Submit
{
private:
    vector<State> states;
    vector<vector<string>> submitted_answers;

public:
    Submit(const int &query_no);
    void submit_answer(const int &query_index, const State &state, const vector<string> &submitted_answer);
    State get_state(const int &query_index);
    vector<string> get_answer(const int &query_index);
    bool is_submitted(const int &query_index);
};

#endif