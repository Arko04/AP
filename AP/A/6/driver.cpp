#include "driver.h"

Driver::Driver(int _driver_id)
{
    driver_id = _driver_id;
}
void Driver::insert_mission(Mission mission)
{
    if (assigned(mission.get_mission_id()))
        throw DuplicateDriverMission();

    missions.push_back(mission);
}
bool Driver::assigned(int mission_id)
{
    for (Mission mission : missions)
        if (mission.get_mission_id() == mission_id)
            return true;

    return false;
}
vector<Mission> Driver::record_ride(Ride ride)
{
    vector<Mission> completed_missions;
    for (int i = 0; i < missions.size(); i++)
    {
        missions[i].add_ride_info(ride);
        if (missions[i].get_completed())
            completed_missions.push_back(missions[i]);
            missions.erase(missions.begin()+i);
    }
    return completed_missions;
}