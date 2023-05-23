#pragma once
#include "mission.hpp"
#include <vector>
using namespace std;

class Driver
{
public:
    Driver(int _driver_id);
    int get_driver_id() { return driver_id; }
    void insert_mission(shared_ptr<Mission> mission);
    vector<shared_ptr<Mission>> record_ride(shared_ptr<Ride> ride);
    void show_missions_status();
    void show_completed_missions(vector<shared_ptr<Mission>> completed_missions);

private:
    bool assigned(int mission_id);

    int driver_id;
    vector<shared_ptr<Mission>> missions;
};