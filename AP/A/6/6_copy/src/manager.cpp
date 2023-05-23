#include "manager.hpp"
#include <memory>
// for (string word : command_fields)
//     cout << word << ' ';
// cout << endl;
void Manager::add_time_mission(vector<string> command_fields)
{

    if (command_fields.size() < 5)
        throw invalid_argument("");

    int mission_id = stoi(command_fields[0]);
    LLInt start_timestamp = stoll(command_fields[1]);
    LLInt end_timestamp = stoll(command_fields[2]);
    int target_time_in_minutes = stoi(command_fields[3]);
    int reward_amount = stoi(command_fields[4]);

    if (!added(mission_id))
    {
        shared_ptr<TimeMission> time_mission = make_shared<TimeMission>(
            mission_id, start_timestamp, end_timestamp, target_time_in_minutes, reward_amount);

        missions.push_back(time_mission);
    }
}
void Manager::handle_adding_time_mission(vector<string> command_fields)
{
    // for (string word : command_fields)
    //     cout << word << ' ';
    // cout << endl;
    try
    {
                // cout << missions.size() << endl;

        add_time_mission(command_fields);
        cout << "OK" << endl;
        // cout << missions.size() << endl;
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (DuplicateMissionID &ex)
    {
        cout << "DUPLICATE_MISSION_ID" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}
void Manager::add_distance_mission(vector<string> command_fields)
{
    if (command_fields.size() < 5)
        throw invalid_argument("");

    int mission_id = stoi(command_fields[0]);
    LLInt start_timestamp = stoll(command_fields[1]);
    LLInt end_timestamp = stoll(command_fields[2]);
    int target_distance_in_meters = stoi(command_fields[3]);
    int reward_amount = stoi(command_fields[4]);

    if (!added(mission_id))
    {
        shared_ptr<DistanceMission> distance_mission = make_shared<DistanceMission>(
            mission_id, start_timestamp, end_timestamp, target_distance_in_meters, reward_amount);

        missions.push_back(distance_mission);
    }
}
void Manager::handle_adding_distance_mission(vector<string> command_fields)
{
    // for (string word : command_fields)
    //     cout << word << ' ';
    // cout << endl;
    try
    {
            //    cout << missions.size() << endl;

         add_distance_mission(command_fields);
        cout << "OK" << endl;
        // cout << missions.size() << endl;
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (DuplicateMissionID &ex)
    {
        cout << "DUPLICATE_MISSION_ID" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}
void Manager::add_count_mission(vector<string> command_fields)
{
    if (command_fields.size() < 5)
        throw invalid_argument("");

    int mission_id = stoi(command_fields[0]);
    LLInt start_timestamp = stoll(command_fields[1]);
    LLInt end_timestamp = stoll(command_fields[2]);
    int target_number = stoi(command_fields[3]);
    int reward_amount = stoi(command_fields[4]);

    if (!added(mission_id))
    {
        shared_ptr<CountMission> count_mission = make_shared<CountMission>(
            mission_id, start_timestamp, end_timestamp, target_number, reward_amount);
    //cout<<"gagoool"<<endl;
        missions.push_back(count_mission);
    }
}
void Manager::handle_adding_count_mission(vector<string> command_fields)
{
    // for (string word : command_fields)
    //     cout << word << ' ';
    // cout << endl;
    try
    {
    //    cout << missions.size() << endl;
         add_count_mission(command_fields);
        cout << "OK" << endl;
        // cout << missions.size() << endl;
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (DuplicateMissionID &ex)
    {
        cout << "DUPLICATE_MISSION_ID" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}

void Manager::assign_mission(vector<string> command_fields)
{
    if (command_fields.size() < 2)
        throw invalid_argument("");

    int mission_id = stoi(command_fields[0]);
    int driver_id = stoi(command_fields[1]);

    shared_ptr<Mission> mission = find_mission(mission_id);
    shared_ptr<Driver> driver = find_driver(driver_id);
    //cout <<drivers.size();
    driver->insert_mission(mission);
}
void Manager::handle_assigning_mission(vector<string> command_fields)
{
    try
    {
        assign_mission(command_fields);
        cout << "OK" << endl;
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (MissionNotFound &ex)
    {
        cout << "MISSION_NOT_FOUND" << endl;
    }
    catch (DuplicateDriverMission &ex)
    {
        cout << "DUPLICATE_DRIVER_MISSION" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}

void Manager::record_ride(vector<string> command_fields)
{
    if (command_fields.size() < 4)
        throw invalid_argument("");

    LLInt start_timestamp = stoll(command_fields[0]);
    LLInt end_timestamp = stoll(command_fields[1]);
    int driver_id = stoi(command_fields[2]);
    int distance = stoi(command_fields[3]);

    shared_ptr<Ride> ride = make_shared<Ride>(start_timestamp, end_timestamp, distance);
    shared_ptr<Driver> driver = find_driver(driver_id);
    vector<shared_ptr<Mission>> completed_missions = driver->record_ride(*ride);
     driver->show_completed_missions(completed_missions);
}
void Manager::handle_recording_ride(vector<string> command_fields)
{
    try
    {
        record_ride(command_fields);
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}
void Manager::show_missions_status(vector<string> command_fields)
{
    if (command_fields.size() < 1)
        throw invalid_argument("");

    int driver_id = stoi(command_fields[0]);
    shared_ptr<Driver> driver = find_driver(driver_id);
    driver->show_missions_status();
}
void Manager::handle_showing_missions_status(vector<string> command_fields)
{
    try
    {
        show_missions_status(command_fields);
    }
    catch (invalid_argument &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
    catch (DriverMissionNotFound &ex)
    {
        cout << "DRIVER_MISSION_NOT_FOUND" << endl;
    }
    catch (out_of_range &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}
// void Manager::init_count_mission(
//     const vector <string>& command_fields,
//         int &mission_id,
//         LLInt &start_timestamp,
//         LLInt &end_timestamp,
//         int &target_number,
//         int &reward_amount)
//         {
//             init_mission(command_fields,mission_id,start_timestamp, end_timestamp, reward_amount );
//             target_number = stoi(command_fields[3]);
//         }

//     void Manager::init_mission(
//         const vector <string>& command_fields,
//         int &mission_id,
//         LLInt &start_timestamp,
//         LLInt &end_timestamp,
//         int &reward_amount)
//         {
//             init_timestamp(command_fields, start_timestamp,end_timestamp);
//             mission_id = stoi(command_fields[0]);
//             reward_amount = stoi(command_fields[4]);
//         }

//     void Manager::init_timestamp(

//        const vector <string>& command_fields,
//         LLInt &start_timestamp,
//         LLInt &end_timestamp)
//         {
//             start_timestamp = stoll(command_fields[1]);
//             end_timestamp =stoll(command_fields[2]);
//         }

bool Manager::added(int mission_id)
{
    for (shared_ptr<Mission> mission : missions)
        if (mission->get_mission_id() == mission_id)
            throw DuplicateMissionID();

    return false;
}
shared_ptr<Mission> Manager::find_mission(int mission_id)
{
    for (shared_ptr<Mission> &mission : missions)
        if (mission->get_mission_id() == mission_id)
            return mission;

    throw MissionNotFound();
}

shared_ptr<Driver> Manager::find_driver(int driver_id)
{
    //cout <<"hoy"<<driver_id <<endl;
    try
    {
        for (shared_ptr<Driver> driver : drivers)
            if (driver->get_driver_id() == driver_id)
                return driver;

        throw DriverNotFound();
    }
    catch (DriverNotFound &ex)
    {
        //cout <<"not_found\n";
        shared_ptr<Driver> driver = make_shared<Driver>(driver_id);
        drivers.push_back(driver);
        return driver;
    }
}