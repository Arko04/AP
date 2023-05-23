#include "timestamp.hpp"

Timestamp::Timestamp(LLInt _start_timestamp, LLInt _end_timestamp)
{
    if(end_timestamp < start_timestamp)
        throw invalid_argument("");

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
Timestamp& Timestamp::operator=(const Timestamp &timestamp)
{
    this->start_timestamp = timestamp.start_timestamp;
    this->end_timestamp = timestamp.end_timestamp;
    return *this;
}