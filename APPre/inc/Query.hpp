#ifndef _QUERY_
#define _QUERY_

#include <iostream>
#include <vector>
#include <memory>
#include "Submit.hpp"
using namespace std;

struct QueryInfo
{
    string question;
    string question_type;
    vector<string> choices;
    vector<string> answers;
};

class Query
{
protected:
    static int question_id;
    int question_index;

    string question;
    string type;
    Query(QueryInfo query_info);

public:
    static shared_ptr<Query> create_query(const QueryInfo &query_info);
    virtual void print_query();
    virtual State is_answer_correct(const vector<string> &submitted_answers) = 0;
    virtual vector<string> get_answer() = 0;
};

#endif