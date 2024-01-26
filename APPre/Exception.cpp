
#include "Exception.hpp"

Error::Error(const string& _ex)
{
    ex = _ex;
}

string Error::what()
{
    return ex;
}

NoInput::NoInput(const string& _ex) : Error(_ex)
{
}
MultipleAnswer::MultipleAnswer(const string& _ex) : Error(_ex)
{
}
InvalidInput::InvalidInput(const string& _ex) : Error(_ex)
{
}
OutOfChoices::OutOfChoices(const string& _ex) : Error(_ex)
{
}
OutOfQuery::OutOfQuery(const string& _ex) : Error(_ex)
{
}
DoubleAnswer::DoubleAnswer(const string& _ex) : Error(_ex)
{
}