#include "QuizMaker.hpp"
#include "QueryParser.hpp"
#include "Const.hpp"
#include <fstream>
#include <vector>

QuizMaker::QuizMaker(string file_name)
{
    ifstream input(file_name);
    string query;
    QueryParser parser;
    while (getline(input, query, QUERY_DEL))
    {
        QueryInfo query_info = parser.parse(query);
        queries.push_back(Query::create_query(query_info)); /////////////////////////////////////
    }
    //////////////
    for (int i = 0; i < queries.size(); i++)
    {
        queries[i]->print_query();
    }
    ////////////////
}

int QuizMaker::get_quiz_no()
{
    return queries.size();
}

// vector<string> QuizMaker::get_answer(const int query_no)
// {
//     return queries[query_no - 1]->get_answer();
// }

State QuizMaker::is_answer_correct(const int query_index, vector<string> submitted_answer)
{
    return queries[query_index - 1]->is_answer_correct(submitted_answer);
}

void QuizMaker::print_more_info(const int query_index)
{
    queries[query_index - 1]->print_more_info();
}