#ifndef _CONST_
#define _CONST_

const char QUERY_DEL = '#';
const char LINE_DEL = '\n';
const char ANS_DEL = ' ';
const char SPACE = ' ';
const char START_NUM = '0';
const char END_NUM = '9';

const int FILE_NAME_INDEX = 1;
const int QUERY_TYPE_INDEX = 0;
const int ANS_INDEX = 0;
const int ANS_BEGINNING_INDEX = 2;
const int COMMAND_INDEX = 0;
const int QUESTION_INDEX = 1;
const int CHOICES_COUNT_INDEX = 2;
const int MULTI_ANSWER_INDEX = 2;
const int NUM_OF_SINGLE_ANSWER = 1;

const string EMPTY = "";
const string MORE_INFO_DEL = ", ";
const string STATE_DEL = " | ";
const string SINGLE_ANSWER = "single_answer";
const string MULTI_ANSWER = "multiple_answer";
const string SHORT_ANSWER = "short_answer";
const string SUBMIT_ANS = "submit_answer";
const string FINISH_EXAM = "finish_exam";
const string CORRECT_ANS = "correct answer.";
const string WRONG_ANS = "wrong answer.";
const string CORRECT_ANSWER = "correct answer:";
const string YOUR_ANSWER = "your answer:";
const string CORRECT = "correct";
const string WRONG = "wrong";
const string NO_ANSWER = "no_answer";
const string FINAL_GRADE = "final grade: ";

const string NO_INPUT = "Not enough input";
const string NO_INPUT_ANSWER = "You didn't enter any answer.";
const string WITHOUT_QUESTION_INDEX = "Not enough input.";
const string ANSWER_INDEX_IS_NOT_INTEGER = "Your answer indexex should be an integer number.";
const string QUESTION_INDEX_IS_NOT_INTEGER = "Question index must be integer.";
const string OUT_OF_CHOICES = "The submitted answer indexes is out of range of possible choices.";
const string COMMAND_NOT_FOUND = "Command not found.";
const string OUT_OF_QUERY = "This question does not exist.";
const string DOUBLE_ANSWER = "You have answered this question before.";
const string MULTI_ANSWER_FOR_SHORT_ANSWER = "Short answer must be a compact statement without no space between.";
const string MULTI_ANSWER_FOR_SINGLE_ANSWER = "You shouldn't enter more than one answer for a single-answer question.";

#endif