#include "QuizInterface.hpp"
#include "QueryParser.hpp"
#include "Utility.hpp"
#include "Const.hpp"
#include "Exception.hpp"
#include <cmath>

QuizInterface::QuizInterface(string inp_file)
{
    quiz = make_shared<QuizMaker>(inp_file);
    const int quiz_no = quiz->get_quiz_no();
    submit = make_shared<Submit>(quiz_no);
}

void QuizInterface::get_answer(bool &finished)
{
    string line;
    while (getline(cin, line))
    {
        vector<string> tokens = Utility::split_by(line, ANS_DEL);
        if (tokens.size() == 0)
        {
            throw NoInput(NO_INPUT);
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
            finished = true;
            break;
        }
        else
        {
            throw InvalidInput(COMMAND_NOT_FOUND);
        }
    }
}

void QuizInterface::handle_input()
{
    bool finished = false;
    while (true)
    {
        try
        {
            get_answer(finished);
            if (finished)
                break;
        }
        catch ( NoInput &e)
        {
            cerr << e.what() << endl;
        }
        catch ( InvalidInput &ex)
        {
            cerr << ex.what() << endl;
        }
        catch ( OutOfChoices &ex)
        {
            cerr << ex.what() << endl;
        }
        catch ( OutOfQuery &ex)
        {
            cerr << ex.what() << endl;
        }
        catch ( DoubleAnswer &ex)
        {
            cerr << ex.what() << endl;
        }
        catch ( exception &ex)
        {
        }
    }
}

State QuizInterface::submit_answer(vector<string> tokens)
{
    // check if input is correct(it is number or string or the size);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (tokens.size() <= QUESTION_INDEX)
    {
        cout << 4;
        throw NoInput(WITHOUT_QUESTION_INDEX);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!Utility::is_integer(tokens[QUESTION_INDEX]))
    {
        cout <<Utility::is_integer(tokens[QUESTION_INDEX]);
        cout  << tokens[QUESTION_INDEX] <<5;;
        throw InvalidInput(QUESTION_INDEX_IS_NOT_INTEGER);
    }
    const int query_no = stoi(tokens[QUESTION_INDEX]);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (tokens.size() <= ANS_BEGINNING_INDEX)
    {
        cout << 7;
        throw NoInput(NO_INPUT_ANSWER);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(query_no > quiz->get_quiz_no())

    {
        throw OutOfQuery(OUT_OF_QUERY);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(submit->is_submitted(query_no))
    {
        cout << 8;
        throw DoubleAnswer(DOUBLE_ANSWER);
    }
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
    for (int i = 1; i <= query_no; i++)
    {
        cout << i << SPACE;
        State state = submit->get_state(i);
        if (state == correct)
        {
            // cout << CORRECT << endl;
            correct_no++;
            print_correct_answer();
        }
        else
        {
            vector<string> answers = quiz->get_answer(i);
            if (state == wrong)
            {
                vector<string> submitted_answers = submit->get_answer(i);
                print_wrong_answer(answers, submitted_answers);
                // cout << WRONG << STATE_DEL;
                // cout << CORRECT_ANSWER;
                // for (int i = 0; i < answers.size(); i++)
                // {
                //     cout << SPACE << answers[i];
                // }
                // // quiz->print_more_info(i);
                // cout << MORE_INFO_DEL;
                // // submit->print_more_info(i);

                // cout << YOUR_ANSWER;
                // for (int i = 0; i < submitted_answer.size(); i++)
                // {
                //     cout << SPACE << submitted_answer[i];
                // }
                // cout << endl;
            }
            else
            {
                print_no_answer(answers);
                // cout << NO_ANSWER << STATE_DEL;
                // // quiz->print_more_info(i);
                // cout << CORRECT_ANSWER;
                // for (int i = 0; i < answers.size(); i++)
                // {
                //     cout << SPACE << answers[i];
                // }
                // //
                // cout << endl;
            }
        }
    }
    if (query_no != 0)
    {
        const float grade = float(correct_no) / float(query_no);
        cout << FINAL_GRADE << (floor(grade * 1000)) / 10.0 << endl;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
        const float grade = 100;
        cout << grade <<endl;
        // throw exception();
    }
    // exit(EXIT_SUCCESS);
}
void QuizInterface::print_correct_answer()
{
    cout << CORRECT << endl;
}
void QuizInterface::print_wrong_answer(const vector<string> answers, const vector<string> submitted_answers)
{
    cout << WRONG << STATE_DEL;
    // cout << CORRECT_ANSWER;
    // for (int i = 0; i < answers.size(); i++)
    // {
    //     cout << SPACE << answers[i];
    // }
    print_answers(answers);
    // quiz->print_more_info(i);
    cout << MORE_INFO_DEL;
    // submit->print_more_info(i);

    // cout << YOUR_ANSWER;
    // for (int i = 0; i < submitted_answers.size(); i++)
    // {
    //     cout << SPACE << submitted_answers[i];
    // }
    print_submitted_answers(submitted_answers);
    cout << endl;
}

void QuizInterface::print_no_answer(const vector<string> answers)
{
    cout << NO_ANSWER << STATE_DEL;
    // quiz->print_more_info(i);
    print_answers(answers);
    //
    cout << endl;
}

void QuizInterface::print_answers(vector<string> answers)

{
    cout << CORRECT_ANSWER;
    for (int i = 0; i < answers.size(); i++)
    {
        cout << SPACE << answers[i];
    }
}
void QuizInterface::print_submitted_answers(vector<string> submitted_answers)

{
    cout << YOUR_ANSWER;
    for (int i = 0; i < submitted_answers.size(); i++)
    {
        cout << SPACE << submitted_answers[i];
    }
}