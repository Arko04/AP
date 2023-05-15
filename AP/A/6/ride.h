#pragma once
#include "timestamp.h"

class Ride {
public : 
    Ride(LLInt _start_timestamp, LLInt _end_timestamp, int _distance);
private:
Timestamp timestamp;
int distance;

};