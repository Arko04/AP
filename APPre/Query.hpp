#ifndef QUERY
#define QUERY
#include <iostream>
#include <vector>
#include <set>
#include "Submit.hpp"
using namespace std;
struct QueryInfo
{
    string question;
    string question_type;
    vector <string> choices;
    vector <string> answers;
};

class Query{
    protected:
        static int question_id;
        int question_index;

        string question;
        string type;
        Query(QueryInfo query_info);
    public:
        static shared_ptr<Query> create_query(QueryInfo query_info);
        virtual void print_query();
        virtual State is_answer_correct(const vector<string> submitted_answers) = 0;
        virtual void print_more_info() = 0;
};
#endif