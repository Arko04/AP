#include "QuizInterface.hpp"
#include "QueryParser.hpp"
#include "Const.hpp"
#include <cmath>

QuizInterface::QuizInterface(string inp_file)
{
    quiz = make_shared<QuizMaker>(inp_file);
    const int quiz_no = quiz->get_quiz_no();
    submit = make_shared<Submit>(quiz_no);
}

void QuizInterface::get_answer()
{
    string line;
    while (getline(cin, line))
    {
        vector<string> tokens = QueryParser::split_by(line, ANS_DEL);
        if (tokens.size() == 0)
        {
            throw exception();
        }
        if (tokens[COMMAND_INDEX] == SUBMIT_ANS)
        {
            State state = submit_answer(tokens);
            cout << ((state == correct) ? CORRECT_ANS : WRONG_ANS) << endl;
        }
        // i suppose if user enter somthing after finish exam command, it doesn't matter.
        else if (tokens[COMMAND_INDEX] == FINISH_EXAM)
        {
            finish_exam();
        }
        else
        {
            throw exception();
        }
    }
}

void QuizInterface::handle_input()
{
    while (true)
    {
        try
        {
            get_answer();
        }
        catch (const std::exception &e)
        {
            std::cerr << "you're wrong" << endl;
        }
    }
}

State QuizInterface::submit_answer(vector<string> tokens)
{
    // check if input is correct(it is number or string or the size);
    const int query_no = stoi(tokens[QUESTION_INDEX]);

    vector<string> submitted_answer(tokens.begin() + ANS_BEGINNING_INDEX, tokens.end());
    sort(submitted_answer.begin(), submitted_answer.end());
    // for(int i = 0; i < submitted_answer.size();i++)
    // {
    //     cout <<submitted_answer[i]<<' ';
    // }
    // cout <<endl;
    State state = quiz->is_answer_correct(query_no, submitted_answer);
    submit->submit_answer(query_no, state, submitted_answer);

    return state;
}
void QuizInterface::finish_exam()
{
    int correct_no = 0;
    const int query_no = quiz->get_quiz_no();
    for(int i = 1; i <= query_no; i++)
    {
        cout << i << SPACE;
        State state = submit->get_state(i);
        if(state == correct)
        {
            cout << CORRECT << endl;
            correct_no++;
        }
        else if(state == wrong)
        {
            cout << WRONG << STATE_DEL;
            quiz->print_more_info(i);
            cout << MORE_INFO_DEL;
            submit->print_more_info(i);
        }
        else{
            cout << NO_ANSWER << STATE_DEL;
            quiz->print_more_info(i);
            cout << endl;
        }
        
    }
    const float grade = float(correct_no) / float(query_no);
    cout << FINAL_GRADE << (floor(grade * 1000))/10.0 << endl;
    exit(EXIT_SUCCESS);
}