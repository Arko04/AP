void copy(istream& in, ostream& out) {
	string word;
	while (in >> word) {
		out << word;
	}
}

class Clock() {
public:
	virtual Time now() = 0;
};

class SystemClock : public Clock() {
public:
	virtual Time now() {
		// return system time
	}
};

class TestClock : public Clock() {
public:
	TestClock(Time t) : time(t) {}
	virtual Time now() {
		return time;
	}
private:
	Time time;
};

void handle_adhan(Clock* theClock) {
	Time now = theClock.now();
	// check if it's time to play adhan
	...
}