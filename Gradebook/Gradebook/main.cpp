#include <iostream>
#include <string>

struct grade_details {
	int* points;
	int* weights;
};

struct student_info {
	int db_id;
	int student_id;
	char grade_option;
	std::string name;
	double grade;
	std::string letter_grade;
};

void graded_artifacts(int n, grade_details* gradebook) {
	int* point_array = new int[n];
	std::cout << "Enter possible points of each category (on the same line): ";
	for (int i = 0; i < n; i++) {
		std::cin >> point_array[i];
		std::cin.ignore(1);
	}

	int* weight_array = new int[n];
	std::cout << "Enter weight of each category (on the same line): ";
	for (int i = 0; i < n; i++) {
		std::cin >> weight_array[i];
		std::cin.ignore(1);
	}

	gradebook->points = point_array;
	gradebook->weights = weight_array;
}


void students(int n, student_info* class_info) {
	std::cout << "Enter students (one student per line): " << std::endl;

	for (int i = 0; i < n; i++) {
		student_info* student = new student_info;
		student->db_id = i;
		std::cin >> student->student_id;
		std::cin.ignore(1);
		std::cin >> student->grade_option;
		std::cin.ignore(1);
		std::cin >> student->name;
		std::cin.ignore(1);
		class_info[i] = *student;
		delete student;
	}
}

void raw_scores(int p, int** class_raw, int n) {
	std::cout << "Enter raw scores for each student (one student per line): " << std::endl;
	for (int i = 0; i < p; i++) {
		int* temp_array = new int[n+1];
		for (int j = 0; j <= n; j++) {
			std::cin >> temp_array[j];
		}
		class_raw[i] = temp_array;
	}
}

void cutpoints(double* cuts) {
	std::cout << "A+: ";
	std::cin >> cuts[0];
	std::cout << "A: ";
	std::cin >> cuts[1];
	std::cout << "A-: ";
	std::cin >> cuts[2];
	std::cout << "B+: ";
	std::cin >> cuts[3];
	std::cout << "B: ";
	std::cin >> cuts[4];
	std::cout << "B-: ";
	std::cin >> cuts[5];
	std::cout << "C+: ";
	std::cin >> cuts[6];
	std::cout << "C: ";
	std::cin >> cuts[7];
	std::cout << "C-: ";
	std::cin >> cuts[8];
	std::cout << "D+: ";
	std::cin >> cuts[9];
	std::cout << "D: ";
	std::cin >> cuts[10];
	std::cout << "D-: ";
	std::cin >> cuts[11];
	std::cout << "F: ";
	std::cin >> cuts[12];
}

void grade(double** raw_overall, int n, grade_details* gradebook, int p, int** class_raw) {
	for (int i = 0; i < p; i++) {
		double* temp = new double[2];
		temp[0] = class_raw[i][0];
		double overall = 0;
		for (int h = 0; h < n; h++) {
			overall += gradebook->weights[h] * class_raw[i][h+1] / gradebook->points[h];
		}
		temp[1] = overall;
		raw_overall[i] = temp;
	}
}
std::string letter_grade(double num_grade, double* cuts) {
	if (num_grade >= cuts[0]) {
		return "A+";
	}
	else if (cuts[0] > num_grade >= cuts[1]) {
		return "A";
	}
	else if (cuts[1] > num_grade >= cuts[2]) {
		return "A-";
	}
	else if (cuts[2] > num_grade >= cuts[3]) {
		return "B+";
	}
	else if (cuts[3] > num_grade >= cuts[4]) {
		return "B";
	}
	else if (cuts[4] > num_grade >= cuts[5]) {
		return "B-";
	}
	else if (cuts[5] > num_grade >= cuts[6]) {
		return "C+";
	}
	else if (cuts[6] > num_grade >= cuts[7]) {
		return "C";
	}
	else if (cuts[7] > num_grade >= cuts[8]) {
		return "C-";
	}
	else if (cuts[8] > num_grade >= cuts[9]) {
		return "D+";
	}
	else if (cuts[9] > num_grade >= cuts[10]) {
		return "D";
	}
	else if (cuts[10] > num_grade >= cuts[11]) {
		return "D-";
	}
	else if (num_grade <= cuts[12]) {
		return "D";
	}
}

void final_grade(int p, double** raw_overall, double* cuts, int m, student_info* class_info) {
	for (int i = 0; i < p; i++) {
		for (int h = 0; h < m; h++) {
			if (raw_overall[i][0] == class_info[h].student_id) {
				class_info[h].grade = raw_overall[i][1];
				class_info[h].letter_grade = letter_grade(class_info[h].grade, cuts);
			}
		}


	}
}

int main() {
	int n;
	int m;

	std::cout << "Enter number of categories: ";
	std::cin >> n;
	grade_details* gradebook = new grade_details;
	graded_artifacts(n, gradebook);

	std::cout << "Enter number of students: ";
	std::cin >> m;
	student_info* class_info = new student_info[m];
	students(m, class_info);

	std::cout << "Enter number of students for the raw scores: ";
	int p;
	std::cin >> p;
	int** class_raw = new int*[p];
	raw_scores(p, class_raw, n);
	

	std::cout << "Enter grade for each cutpoint: ";
	double* cuts = new double[13];
	cutpoints(cuts);
	
	double** raw_overall = new double*[p];
	grade(raw_overall, n, gradebook, p, class_raw);

	final_grade(p, raw_overall, cuts, m, class_info);

	for (int i = 0; i < p; i++) {
		std::cout << "db_id: " << class_info[i].db_id << std::endl;
		std::cout << "student_id: " << class_info[i].student_id << std::endl;
		std::cout << "grade_option: " << class_info[i].grade_option << std::endl;
		std::cout << "name: " << class_info[i].name << std::endl;
		std::cout << "grade: " << class_info[i].grade << std::endl;
		std::cout << "letter_grade: " << class_info[i].letter_grade << std::endl;
	}

	system("Pause");
	return 0;
}