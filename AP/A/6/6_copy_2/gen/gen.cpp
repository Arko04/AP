// #include <bits/stdc++.h>
#include <iostream>
#include <string>
// #include <vector>
#include <random>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define endl '\n'

string random_sign() { return rng()%3 ? "" : "-"; }
string random_id() { return to_string(rng()%10); }
string random_timestamp() { return to_string(time(0) + (rng()%100000)); }
string random_money() { return to_string((rng()%10+1)*400); }
string random_component() { return to_string(rng()%30+1); }
string gen_full_cmd() {
    switch (rng()%7) {
        case 0:
            return "add_time_mission " + random_id() + " " + random_timestamp() + " " + random_timestamp() + " " + random_sign() + random_component() + " " + random_sign() + random_money();
        case 1:
            return "add_distance_mission " + random_id() + " " + random_timestamp() + " " + random_timestamp() + " " + random_sign() + random_component() + " " + random_sign() + random_money();
        case 2:
            return "add_count_mission " + random_id() + " " + random_timestamp() + " " + random_timestamp() + " " + random_sign() + random_component() + " " + random_sign() + random_money();
        case 3:
            return "assign_mission " + random_id() + " " + random_id();
        case 4:
            return "record_ride " + random_timestamp() + " " + random_timestamp() + " " + random_id() + " " + random_component();
        default:
            return "show_missions_status " + random_id();
    }
}

void make_input(){
    int commands_cnt = rng()%100+1;
    freopen("input.txt", "w", stdout);
    while (commands_cnt--)
        cout << gen_full_cmd() << endl;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
    make_input();
    
    return 0;
}
