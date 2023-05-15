#include "timestamp.h"

Timestamp::Timestamp(LLInt _start_timestamp, LLInt _end_timestamp)
{
    if(end_timestamp < start_timestamp)
        throw InvalidArgument();

    start_timestamp = _start_timestamp; 
    end_timestamp = _end_timestamp;
}
