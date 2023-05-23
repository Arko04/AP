#pragma once
#include "exception.hpp"
#include <iostream>
using namespace std;
using LLInt = long long int; 

class Timestamp{

    public:
    Timestamp(LLInt, LLInt);
    LLInt get_start_timestamp() { return start_timestamp;}
    LLInt get_end_timestamp(){return end_timestamp;}
    int calc_time_gap_in_minute(); 
    void set_end_timestamp(LLInt _end_timestamp);
    Timestamp& operator=(const Timestamp &timestamp);

    private:
    LLInt start_timestamp;
    LLInt end_timestamp;

};