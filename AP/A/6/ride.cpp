
#include "ride.h"
Ride::Ride(LLInt _start_timestamp, LLInt _end_timestamp, int _distance):timestamp(_start_timestamp, _end_timestamp)
{
    distance = _distance;
}