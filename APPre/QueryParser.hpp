#ifndef _QUERY_PARSER_
#define _QUERY_PARSER_

#include <iostream>
#include <vector>
#include "Query.hpp"
using namespace std;

class QueryParser
{
private:
    vector<string> tokenize(string query);
    vector<string> normalize(vector<string> tokens);

    QueryInfo create_single_query_info(vector<string> query);
    QueryInfo create_multi_query_info(vector<string> query);
    QueryInfo create_non_short_query_info(vector<string> query);
    QueryInfo create_short_query_info(vector<string> query);

    vector<string> get_choices(vector<string> query);
    vector<string> get_answers(vector<string> query, const int choices_count);

public:
    QueryInfo parse(string query);
};

#endif