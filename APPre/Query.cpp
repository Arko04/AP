#include "Query.hpp"
#include "Const.hpp"
#include "SingleAnswer.hpp"
#include "MultiAnswer.hpp"
#include "ShortAnswer.hpp"
#include "Exception.hpp"

int Query::question_id = 1;

Query::Query(QueryInfo query_info)
{
    question = query_info.question;
    type = query_info.question_type;
    question_index = question_id;
    question_id++;
}

shared_ptr<Query> Query::create_query(const QueryInfo &query_info)
{
    if (query_info.question_type == SINGLE_ANSWER)
    {
        return make_shared<SingleAnswer>(query_info);
    }
    else if (query_info.question_type == MULTI_ANSWER)
    {
        return make_shared<MultiAnswer>(query_info);
    }
    else if (query_info.question_type == SHORT_ANSWER)
    {
        return make_shared<ShortAnswer>(query_info);
    }
    else
    {
        throw InvalidInput(COMMAND_NOT_FOUND);
    }
}

void Query::print_query()
{
    cout << question_index << STATE_DEL << type << endl;
    cout << question << endl;
}
