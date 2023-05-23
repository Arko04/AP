#include "mission.hpp"

class CountMission : public Mission
{
public:
    CountMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_number,
        int _reward_amount);
    virtual void add_ride_info(shared_ptr<Ride> ride) override;
    //CountMission(const shared_ptr<CountMission> count_mission);
             //   virtual void set_mission(const shared_ptr<CountMission> count_mission);

                std::shared_ptr<Mission> clone() const override {
        return std::make_shared<CountMission>(*this);
    }


private:
    int target_number;
    int total_ride_number;
};