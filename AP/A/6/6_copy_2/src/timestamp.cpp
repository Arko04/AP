#include "timestamp.hpp"
#include "const.hpp"
#include <stdexcept>
#include<iostream>
Timestamp::Timestamp(LLInt _start_timestamp, LLInt _end_timestamp)
{
    if(_end_timestamp < _start_timestamp)
        throw invalid_argument(EMPTY);
    // cout << _end_timestamp<<endl;
    // cout << _start_timestamp <<endl;
    start_timestamp = _start_timestamp; 
    end_timestamp = _end_timestamp;
}
int Timestamp::calc_time_gap_in_minute()
{
    return (end_timestamp - start_timestamp) / 60;
}
void Timestamp::set_end_timestamp(LLInt _end_timestamp)
{
    this->end_timestamp = _end_timestamp;
}
// Timestamp& Timestamp::operator=(const Timestamp &timestamp)
// {
//     this->start_timestamp = timestamp.start_timestamp;
//     this->end_timestamp = timestamp.end_timestamp;
//     return *this;
// }