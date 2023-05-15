#include "mission.h"
#include <vector>
class Driver
{
public:
    Driver(int _driver_id);
    bool get_driver_id() { return driver_id;}
    void insert_mission(Mission mission);
    bool assigned(int mission_id);
    vector<Mission> record_ride(Ride ride);
private:
    int driver_id;
    vector <Mission> missions;

};