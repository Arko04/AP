#include "mission.hpp"
#include <vector>
class Driver
{
public:
    Driver(int _driver_id);
    int get_driver_id() { return driver_id;}
    void insert_mission(shared_ptr<Mission> mission);
    bool assigned(int mission_id);
    vector<shared_ptr<Mission>> record_ride(Ride ride);
    void show_missions_status();
    void show_completed_missions(vector<shared_ptr<Mission>> completed_missions);
private:
    int driver_id;
    vector <shared_ptr<Mission>> missions;

};