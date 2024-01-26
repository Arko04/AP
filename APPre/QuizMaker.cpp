#include "QuizMaker.hpp"
#include "QueryParser.hpp"
#include "Const.hpp"
#include <fstream>
#include <vector>

QuizMaker::QuizMaker(const string &file_name)
{
    ifstream input(file_name);
    string query;
    QueryParser parser;
    while (getline(input, query, QUERY_DEL))
    {
        QueryInfo query_info = parser.parse(query);
        queries.push_back(Query::create_query(query_info));
    }
}

int QuizMaker::get_quiz_no()
{
    return queries.size();
}

State QuizMaker::is_answer_correct(const int &query_index, const vector<string> &submitted_answer)
{
    return queries[query_index - 1]->is_answer_correct(submitted_answer);
}

vector<string> QuizMaker::get_answer(const int &query_index)
{
    return queries[query_index - 1]->get_answer();
}