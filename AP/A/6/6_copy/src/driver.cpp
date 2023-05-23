#include "driver.hpp"

Driver::Driver(int _driver_id)
{
    driver_id = _driver_id;
    //cout << driver_id << endl;
}
void Driver::insert_mission(shared_ptr<Mission> mission)
{
    if (assigned(mission->get_mission_id()))
        throw DuplicateDriverMission();

    missions.push_back(mission);
}
bool Driver::assigned(int mission_id)
{
    for (shared_ptr<Mission> mission : missions)
        if (mission->get_mission_id() == mission_id)
            return true;

    return false;
}
vector<shared_ptr<Mission>> Driver::record_ride(Ride ride)
{
    vector<shared_ptr<Mission>> completed_missions;
    for (int i = 0; i < missions.size(); i++)
    {
        if (!missions[i]->get_completed())
        {
            missions[i]->add_ride_info(ride);
            if (missions[i]->get_completed())
            {
                completed_missions.push_back(missions[i]);
                // missions.erase(missions.begin()+i);
            }
        }
    }
    return completed_missions;
}
bool comp(shared_ptr<Mission> mission1, shared_ptr<Mission> mission2){
    return mission1->get_timestamp().get_start_timestamp() < mission2->get_timestamp().get_start_timestamp();
}
void Driver ::show_missions_status()
{
    if (missions.empty())
        throw DriverMissionNotFound();
    cout << "missions status for driver " << driver_id << ":" << endl;

    // missions should be sorted;
    sort(missions.begin(), missions.end(), comp);
    for (shared_ptr<Mission> &mission : missions)
        mission->show_status();
}
void Driver::show_completed_missions(vector<shared_ptr<Mission>>completed_missions){
    cout <<"completed missions for driver "<<driver_id<<":"<<endl;
    sort(completed_missions.begin(),completed_missions.end(), comp);

    for (shared_ptr<Mission> &mission : completed_missions)
        mission->show_completed_mission_status();
}