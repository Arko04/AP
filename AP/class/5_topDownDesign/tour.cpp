#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct Time {
	int hours;
	int minutes;
};

const Time MIDNIGHT = {24, 0};

struct Attraction {
	string name;
	Time opening_time;
	Time closing_time;
	int rank;
};

typedef vector<Attraction> AttractionList;

struct Visit {
	Attraction attraction;
	Time from_time;
	Time to_time;
};

typedef vector<Visit> Tour;

vector<string> split_by_commas(string str) {
	vector<string> result;
	int start_pos = 0;
	while (start_pos < str.length()) {
		int comma_pos = str.find(",", start_pos);
		if (comma_pos == string::npos) {
			result.push_back(str.substr(start_pos));
			break;
		}
		result.push_back(str.substr(start_pos, comma_pos - start_pos));
		start_pos = comma_pos + 1;
	}
	return result;
}

Time create_time(string time_str) {
	Time result;
	result.hours = atoi(time_str.substr(0, 2).c_str());
	result.minutes = atoi(time_str.substr(3).c_str());
	return result;
}

string to_string(Time t) {
	ostringstream oss;
	oss << setfill('0') << setw(2) << t.hours << ':' << setw(2) << t.minutes;
	return oss.str();
}

Time add_minutes(Time t, int m) {
	// precondition: the result will not be greater than 23:59
	Time result = t;
	result.minutes += m;
	result.hours += (result.minutes / 60);
	result.minutes %= 60;
	return result;
}

bool not_before(Time t1, Time t2) {
	return (t1.hours > t2.hours) || ((t1.hours == t2.hours) && (t1.minutes >= t2.minutes));
}

bool not_after(Time t1, Time t2) {
	return (t1.hours < t2.hours) || ((t1.hours == t2.hours) && (t1.minutes <= t2.minutes));
}

bool after(Time t1, Time t2) {
    return (t1.hours > t2.hours) || ((t1.hours == t2.hours) && (t1.minutes > t2.minutes));
}

bool same(Time t1, Time t2) {
	return (t1.hours == t2.hours) && (t1.minutes == t2.minutes);
}

Time min(Time t1, Time t2) {
	return not_after(t1, t2) ? t1 : t2;
}

Time max(Time t1, Time t2) {
	return not_before(t1, t2) ? t1 : t2;
}

Attraction read_attraction(string str) {
	vector<string> fields = split_by_commas(str);
	Attraction new_attraction;
	new_attraction.name = fields[0];
	new_attraction.opening_time = create_time(fields[1]);
	new_attraction.closing_time = create_time(fields[2]);
	new_attraction.rank = stoi(fields[3]);
	return new_attraction;
}

AttractionList read_attractions_info(string filename) {
	AttractionList attrs;
	ifstream input_csv(filename);

	string line;
	getline(input_csv, line);	// skip the header row in the CSV file

	while (getline(input_csv, line)) {
		attrs.push_back(read_attraction(line));
	}

	input_csv.close();
	return attrs;
}

void print_attraction(Attraction attr) {
	cout << attr.name << '\t' 
		 << attr.opening_time.hours << ':' << attr.opening_time.minutes << '\t'
		 << attr.closing_time.hours << ':' << attr.closing_time.minutes << '\t'
		 << attr.rank << endl;
}

void print_attractions(AttractionList attrs) {
	for (Attraction attr : attrs)
		print_attraction(attr);
	cout << endl;
}

void print_visit(const Visit& visit) {
	cout << "Location " << visit.attraction.name << endl
         << "Visit from " << to_string(visit.from_time) 
         << " until " << to_string(visit.to_time) << endl << "---" << endl;
}

void print_tour(const Tour& tour) {
	for (Visit visit : tour) {
		print_visit(visit);
	}
}

bool theres_enough_time_to_visit(Attraction attraction, Time time) {
	return not_before(attraction.closing_time, add_minutes(time, 15));
}

bool already_visited(Tour tour, Attraction attraction) {
	for (Visit visit : tour) {
		if (visit.attraction.name == attraction.name)
			return true;
	}
	return false;
}

Visit create_visit(Attraction attraction, Time visit_time) {
	Visit result;
	result.attraction = attraction;
	result.from_time = visit_time;
	result.to_time = min(attraction.closing_time, add_minutes(visit_time, 60));
	return result;
}

Tour plan_tour(AttractionList attractions, Time time) {
	Tour tour;
    while (true) {
		bool found_something = false;
		Visit best_earliest;
		best_earliest.from_time = MIDNIGHT;
	    for (Attraction attraction : attractions) {
	    	if (not_after(attraction.closing_time, time))
	    		continue;
	    	if (already_visited(tour, attraction))
	    		continue;
	    	Time visit_time = max(time, attraction.opening_time);
	    	if (!theres_enough_time_to_visit(attraction, visit_time))
	    		continue;
	    	if (after(best_earliest.from_time, visit_time) || 
	    			(same(visit_time, best_earliest.from_time)) && (attraction.rank < best_earliest.attraction.rank)) {
	    		best_earliest = create_visit(attraction, visit_time);
	    		found_something = true;
	    	}
	    }
	    if (!found_something)
		    break;
   		tour.push_back(best_earliest);
   		time = add_minutes(best_earliest.to_time, 30);
    }
    return tour;
}

int main(int argc, char const *argv[]) {
    AttractionList attractions = read_attractions_info(argv[1]);
 	Tour tour = plan_tour(attractions, {8, 0});
	print_tour(tour);	
}