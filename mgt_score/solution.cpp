#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <string>

using namespace std;
#define MAX_N 20005
#define MAX_GRADE 3
const int INF = 0x3F;

struct Student {
	int id;
	int grade;
	int gender;
	int score;
};

struct comparator {
	bool operator() (const Student &a, const Student &b) const {
		if (a.score == b.score) {
			return a.id < b.id;
		}
		return a.score < b.score;
	}
};

set <Student, comparator> studentList[4][2];
unordered_map<int, Student> stud_info;

int convert_gender(string gender) {
	if (gender == "male") {
		return 0;
	} 
	return 1;
}

void init() {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j < 2; j++) {
			studentList[i][j].clear();
		}
	}
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	Student new_stud = { mId, mGrade, convert_gender(mGender), mScore};
	studentList[mGrade][convert_gender(string(mGender))].insert(new_stud);
	stud_info[mId] = new_stud;

	return (*studentList[mGrade][convert_gender(string(mGender))].rbegin()).id;
}

int remove(int mId) {

	if (stud_info.find(mId) == stud_info.end()) {
		return 0;
	}
	Student curr_stud = stud_info[mId];
	int grade = curr_stud.grade;
	int gender = curr_stud.gender;
	int score = curr_stud.score;

	studentList[grade][gender].erase(curr_stud);
	if (studentList[grade][gender].size() == 0) {
		return 0;
	}
	return (*studentList[grade][gender].begin()).id;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	int tmp_max = 99999999;
	int tmp_id = 99999999;

	for (int i = 0; i < mGradeCnt; i++) {
		for (int j = 0; j < mGenderCnt; j++) {
			int gender = convert_gender(mGender[j]);
			int grade = mGrade[i];

			if (studentList[grade][gender].size() == 0 || (*studentList[grade][gender].rbegin()).score < mScore) {
				continue;
			}

			Student tmp_str = { -1, -1, -1, mScore};

			auto a = studentList[grade][gender].lower_bound(tmp_str);
			if (a == studentList[grade][gender].end()) {
				continue;
			}

			if ((*a).score == tmp_max) {
				if ((*a).id < tmp_id) {
					tmp_id = (*a).id;
				}
			} else if ((*a).score < tmp_max) {
				tmp_max = (*a).score;
				tmp_id = (*a).id;
			}
		} 
	}

	if (tmp_id == 99999999) return 0;
	return tmp_id;
}