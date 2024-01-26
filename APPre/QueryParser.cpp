#include "QueryParser.hpp"
#include "Const.hpp"
#include "Utility.hpp"
#include "Exception.hpp"
#include <sstream>

vector<string> QueryParser::normalize(vector<string> tokens)
{
    for (int i = 0; i < tokens.size(); i++)
    {
        while (tokens[i][tokens[i].size() - 1] == ANS_DEL || tokens[i][tokens[i].size() - 1] == LINE_DEL)
        {
            tokens[i].pop_back();
        }
    }
    return tokens;
}

vector<string> QueryParser::tokenize(string query)
{
    vector<string> tokens = Utility::split_by(query, LINE_DEL);
    tokens = normalize(tokens);
    return tokens;
}

QueryInfo QueryParser::parse(string query)
{
    QueryInfo query_info;
    vector<string> tokens = tokenize(query);

    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i] << endl;
        cout << tokens[i][tokens[i].size() - 1] << endl;
    }
    string query_type = tokens[QUERY_TYPE_INDEX];

    if (query_type == SINGLE_ANSWER)
    {
        query_info = create_single_query_info(tokens);
    }
    else if (query_type == MULTI_ANSWER)
    {
        query_info = create_multi_query_info(tokens);
    }
    else if (query_type == SHORT_ANSWER)
    {
        query_info = create_short_query_info(tokens);
    }
    else
    {
        throw InvalidInput(COMMAND_NOT_FOUND);
    }
    return query_info;
}

vector<string> QueryParser::get_choices(vector<string> query)
{
    int choices_count = stoi(query[CHOICES_COUNT_INDEX]);
    vector<string> choices;
    for (int index = 1; index <= choices_count; index++)
    {
        choices.push_back(query[CHOICES_COUNT_INDEX + index]);
    }
    return choices;
}

vector<string> QueryParser::get_answers(vector<string> query, const int choices_count)
{
    int answer_index = CHOICES_COUNT_INDEX + choices_count + 1;
    // stringstream answers_part(query[answer_index]);
    // string answer;
    vector<string> answers = Utility::split_by(query[answer_index], ANS_DEL);
    // int answers_count = 0;
    // while(getline(answers_part, answer, ANS_DEL))
    // {

    //     answers.push_back(answer);
    //     // answers_count++;
    // }
    sort(answers.begin(), answers.end());
    return answers;
}

QueryInfo QueryParser::create_single_query_info(vector<string> query)
{
    return create_non_short_query_info(query);
}

QueryInfo QueryParser::create_multi_query_info(vector<string> query)
{
    return create_non_short_query_info(query);
}

QueryInfo QueryParser::create_non_short_query_info(vector<string> query)
{
    QueryInfo query_info = {.question_type = query[QUERY_TYPE_INDEX], .question = query[QUESTION_INDEX]};
    int choices_count = stoi(query[CHOICES_COUNT_INDEX]);
    query_info.choices = get_choices(query);
    query_info.answers = get_answers(query, choices_count);
    return query_info;
}

QueryInfo QueryParser::create_short_query_info(vector<string> query)
{
    QueryInfo query_info = {.question_type = query[QUERY_TYPE_INDEX], .question = query[QUESTION_INDEX]};
    ;
    query_info.answers.push_back(query[MULTI_ANSWER_INDEX]);
    return query_info;
}