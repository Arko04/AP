class Course {
private:
	string course_no;
	string title;
	int credits;
};

class StudyRecord {
private:
	string term;
	Course* course;
	double grade;
	int status;
};

class Student {
public:
	double gpa() {
		double weighted_sum = 0;
		int total_credits = 0;
		for (StudyRecord rec : transcript) {
			total_credits += rec.get_credits();
			weighted_sum += rec.get_grade() * get_credits();
		}
		return weighted_sum / total_credits;
	}
private:
	string student_no;
	string name;
	vector<StudyRecord> transcript;
};
