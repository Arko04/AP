#ifndef _EXCEPTION_
#define _EXCEPTION_

#include <iostream>
#include <exception>
using namespace std;

class Error : public exception /////////////////////////////////////////////////////////////////////////////////////
{
    public:
        Error(const string& _ex);
        string what();
    private:
         string ex;
};

class OutOfChoices : public Error
{
    public:
        OutOfChoices(const string& _ex);
    private:
};

class OutOfQuery : public Error
{
    public:
        OutOfQuery(const string& _ex);
    private:
}; 

class DoubleAnswer : public Error
{
    public:
        DoubleAnswer(const string& _ex);
    private:
};

class NoInput : public Error
{
    public:
        NoInput(const string& _ex);
    private:
};

class MultipleAnswer : public Error
{
    public:
        MultipleAnswer(const string& _ex);
    private:
};

class InvalidInput : public Error
{
    public:
        InvalidInput(const string& _ex);
    private:
};

#endif