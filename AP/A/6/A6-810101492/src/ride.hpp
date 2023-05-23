#pragma once
#include "timestamp.hpp"

class Ride
{
public:
    Ride(LLInt _start_timestamp, LLInt _end_timestamp, int _distance);
    int get_distance() { return distance; }
    Timestamp get_timestamp() { return timestamp; }

private:
    Timestamp timestamp;
    int distance;
};