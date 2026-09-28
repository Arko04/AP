#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string LOCK = "Location ";
const string NAME = "name";
const string OPENINGTIME = "openingTime";
const string CLOSINGTIME = "closingTime";
const string RANK = "rank";
const string END_PRINT = "---";
const string VISIT_FROM = "Visit from ";
const string UNTIL = " until ";
const int LEASTTIME = 15;
const int MOVETIME = 30;
const int VISITTIME = 60;

struct Attraction
{
    vector<string> name;
    vector<int> opening_time;
    vector<int> closing_time;
    vector<int> rank;
    vector<int> visited;
};

int find_number_of_places(const vector<string> &readed_string)
{
    int num_of_places = readed_string.size() / 4 - 1;
    return num_of_places;
}

vector<int> find_order_of_information(const vector<string> &readed_string)
{
    vector<int> order_of_informations;
    const vector<string> info {NAME, OPENINGTIME, CLOSINGTIME, RANK};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (info[i] == readed_string[j])
                order_of_informations.push_back(j);
    return order_of_informations;
}

int string_to_minutes(string string_time)
{
    int minutes = 0;
    minutes = stoi(string_time.substr(0, 2)) * 60 + stoi(string_time.substr(3, 2));
    return minutes;
}

void push_to_attraction(const vector<string> &input_string, Attraction &attraction, int i)
{
    vector<int> order_of_informations = find_order_of_information(input_string);
    attraction.name.push_back(input_string[order_of_informations[0] + i * 4]);
    attraction.opening_time.push_back(string_to_minutes(input_string[order_of_informations[1] + i * 4]));
    attraction.closing_time.push_back(string_to_minutes(input_string[order_of_informations[2] + i * 4]));
    int rank = stoi(input_string[order_of_informations[3] + i * 4]);
    attraction.rank.push_back(rank);
    attraction.visited.push_back(0);
}

Attraction string_to_struct(const vector<string> &input_string)
{
    Attraction attraction;
    int number_of_places = find_number_of_places(input_string);

    for (int i = 1; i <= number_of_places; i++)
        push_to_attraction(input_string, attraction, i);
    return attraction;
}

Attraction input_attraction_info(string filename)
{
    vector<string> readed_file;
    ifstream input_file(filename);
    string line_of_file;
    while (getline(input_file, line_of_file))
    {
        istringstream line(line_of_file);
        string file_element;
        while (getline(line, file_element, ','))
            readed_file.push_back(file_element);
    }
    input_file.close();
    Attraction attraction = string_to_struct(readed_file);
    return attraction;
}

string minutes_to_string(int input)
{
    string time = "";
    int hours = input / 60;
    int minutes = input % 60;
    if (hours < 10)
        time += "0";
    time += to_string(hours);
    time += ":";
    if (minutes < 10)
        time += "0";
    time += to_string(minutes);
    return time;
}

void print_attraction(int start, int finnish, Attraction attraction, int place_index)
{
    cout << LOCK << attraction.name[place_index] << endl
         << VISIT_FROM << minutes_to_string(start) << UNTIL
         << minutes_to_string(finnish) << endl
         << END_PRINT << endl;
}

bool is_open(int start, int i, Attraction attraction)
{
    return (start >= attraction.opening_time[i] && start <= attraction.closing_time[i]) ? true : false;
}

bool is_visitable(int start, int i, Attraction attraction)
{
    return (start + MOVETIME + LEASTTIME <= attraction.closing_time[i]) ? true : false;
}

int change_visit_index(int start, int visit_index, int i, Attraction attraction)
{
    if (visit_index == -1)
        return i;
    else
    {
        if (start >= attraction.opening_time[i])
            if (attraction.rank[i] < attraction.rank[visit_index])
                return i;
            else
                return visit_index;
        else
        {
            if (attraction.opening_time[i] < attraction.opening_time[visit_index])
                return i;
            if (attraction.opening_time[i] == attraction.opening_time[visit_index])
                if (attraction.rank[i] < attraction.rank[visit_index])
                    return i;
            return visit_index;
        }
    }
}

void change_start(int &start, Attraction attraction, int visit_index)
{
    if (start + MOVETIME < attraction.opening_time[visit_index])
        start = attraction.opening_time[visit_index];
    else
        start += MOVETIME;
}

void change_finnish(int start, int &finnish, Attraction attraction, int visit_index)
{
    if (attraction.closing_time[visit_index] - start >= VISITTIME)
        finnish = start + VISITTIME;
    else
        finnish = attraction.closing_time[visit_index];
}

void make_attraction_visited(int &start, int &finnish, Attraction &attraction, int visit_index)
{
    attraction.visited[visit_index] = 1;
    change_start(start, attraction, visit_index);
    change_finnish(start, finnish, attraction, visit_index);
}

bool is_attraction_possible_to_visit(int start, Attraction attraction, int i)
{
    return (is_open(start, i, attraction) || start < attraction.opening_time[i]) &&
           is_visitable(start, i, attraction) &&
           attraction.visited[i] == 0;
}

int visit_place_index(int &start, int &finnish, Attraction &attraction)
{
    int visit_index = -1;
    for (int i = 0; i < attraction.name.size(); i++)
        if (is_attraction_possible_to_visit(start, attraction, i))
            visit_index = change_visit_index(start, visit_index, i, attraction);
    if (visit_index >= 0)
        make_attraction_visited(start, finnish, attraction, visit_index);
    return visit_index;
}

int main(int argc, char *argv[])
{
    Attraction attraction = input_attraction_info(argv[1]);
    int finnish = 8 * 60, start = 8 * 60 - 30;
    int index_of_place_to_visit = visit_place_index(start, finnish, attraction);
    while (index_of_place_to_visit != -1)
    {
        print_attraction(start, finnish, attraction, index_of_place_to_visit);
        start = finnish;
        index_of_place_to_visit = visit_place_index(start, finnish, attraction);
    }
    return 0;
}