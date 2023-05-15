#pragma once
#include "exception.h"
#include <iostream>
using namespace std;
using LLInt = long long int; 

class Timestamp{

    public:
    Timestamp(LLInt, LLInt);
    LLInt get_start_timestamp();
    LLInt get_end_timestamp();
    LLInt calc_time_gap_in_minute(); 

    private:
    LLInt start_timestamp;
    LLInt end_timestamp;

};