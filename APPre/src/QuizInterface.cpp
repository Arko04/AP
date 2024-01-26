#include "../inc/QuizInterface.hpp"
#include "../inc/QueryParser.hpp"
#include "../inc/Utility.hpp"
#include "../inc/Const.hpp"
#include "../inc/Exception.hpp"
#include <memory>
#include <cmath>
#include <set>

QuizInterface::QuizInterface(const string &inp_file)
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
        catch (NoInput &e)
        {
            cerr << e.what() << endl;
        }
        catch (InvalidInput &ex)
        {
            cerr << ex.what() << endl;
        }
        catch (OutOfChoices &ex)
        {
            cerr << ex.what() << endl;
        }
        catch (OutOfQuery &ex)
        {
            cerr << ex.what() << endl;
        }
        catch (DoubleAnswer &ex)
        {
            cerr << ex.what() << endl;
        }
        catch (MultipleAnswer &ex)
        {
            cerr << ex.what() << endl;
        }
        catch (exception &ex)
        {
        }
    }
}

State QuizInterface::submit_answer(const vector<string> &tokens)
{
    if (tokens.size() <= QUESTION_INDEX)
    {
        throw NoInput(WITHOUT_QUESTION_INDEX);
    }
    if (!Utility::is_integer(tokens[QUESTION_INDEX]))
    {
        throw InvalidInput(QUESTION_INDEX_IS_NOT_INTEGER);
    }
    const int query_no = stoi(tokens[QUESTION_INDEX]);
    if (query_no > quiz->get_quiz_no())
    {
        throw OutOfQuery(OUT_OF_QUERY);
    }
    if (submit->is_submitted(query_no))
    {
        throw DoubleAnswer(DOUBLE_ANSWER);
    }
    if (tokens.size() <= ANS_BEGINNING_INDEX)
    {
        throw NoInput(NO_INPUT_ANSWER);
    }
    set<string> submitted_ans(tokens.begin() + ANS_BEGINNING_INDEX, tokens.end());
    vector<string> submitted_answer(submitted_ans.begin(), submitted_ans.end());

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
            }
            else
            {
                print_no_answer(answers);
            }
        }
    }
    if (query_no != 0)
    {
        const float grade = float(correct_no) / float(query_no);
        cout << FINAL_GRADE << (floor(grade * 1000)) / 10.0 << endl;
    }
    else
    {
        const float grade = 100;
        cout << grade << endl;
    }
}

void QuizInterface::print_correct_answer()
{
    cout << CORRECT << endl;
}

void QuizInterface::print_wrong_answer(const vector<string> &answers, const vector<string> &submitted_answers)
{
    cout << WRONG << STATE_DEL;
    print_answers(answers);
    cout << MORE_INFO_DEL;
    print_submitted_answers(submitted_answers);
    cout << endl;
}

void QuizInterface::print_no_answer(const vector<string> &answers)
{
    cout << NO_ANSWER << STATE_DEL;
    print_answers(answers);
    cout << endl;
}

void QuizInterface::print_answers(const vector<string> &answers)
{
    cout << CORRECT_ANSWER;
    for (int i = 0; i < answers.size(); i++)
    {
        cout << SPACE << answers[i];
    }
}

void QuizInterface::print_submitted_answers(const vector<string> &submitted_answers)

{
    cout << YOUR_ANSWER;
    for (int i = 0; i < submitted_answers.size(); i++)
    {
        cout << SPACE << submitted_answers[i];
    }
}