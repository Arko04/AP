#include <iostream>
#include "driver.hpp"
#include "const.hpp"
#include "exception.hpp"

Driver::Driver(int _driver_id)
{
    driver_id = _driver_id;
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

vector<shared_ptr<Mission>> Driver::record_ride(shared_ptr<Ride> ride)
{
    vector<shared_ptr<Mission>> completed_missions;
    for (shared_ptr<Mission> &mission : missions)
    {
        if (!mission->get_completed())
        {
            mission->add_ride_info(ride);
            // cout <<"onggggggggg\n";
            if (mission->get_completed())
            {
                // cout <<"commmmmmm\n";
                completed_missions.push_back(mission);
            }
        }
    }
    // show_completed_missions(completed_missions);
    return completed_missions;
}

bool comp_start_timestamp(shared_ptr<Mission> mission1, shared_ptr<Mission> mission2)
{
    return mission1->get_timestamp().get_start_timestamp() < mission2->get_timestamp().get_start_timestamp();
}

void Driver ::show_missions_status()
{
    if (missions.empty())
        throw DriverMissionNotFound();
    cout << "missions status for driver " << driver_id << DATA_DELIMITER << endl;

    sort(missions.begin(), missions.end(), comp_start_timestamp);
    for (int i = 0; i < missions.size(); i++)
    {
        missions[i]->show_status();
        if (i < missions.size() - 1)
            cout << endl;
    }
}

void Driver::show_completed_missions(vector<shared_ptr<Mission>> completed_missions)
{
    cout << "completed missions for driver " << driver_id << DATA_DELIMITER << endl;

    sort(completed_missions.begin(), completed_missions.end(), comp_start_timestamp);
    for (int i = 0; i < completed_missions.size(); i++)
    {
        completed_missions[i]->show_completed_mission_status();
        if (i < completed_missions.size() - 1)
            cout << endl;
    }
}