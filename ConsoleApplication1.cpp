#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int NUM_SUBJECTS = 4; // number of subjects
const int NUM_STUDENTS = 25; // number of students
// Student structure
struct Student {
	string name;
	int grades[NUM_SUBJECTS];
};
// Function to add a student
void add_name(Student& student) {
	cout << "Enter a student name: ";
	cin.ignore();
	getline(cin, student.name);
}
// Function to add grade for a student
void add_grades(Student& student) {
	cout << "add student grades for " << student.name << " :  ";
	for (int i = 0; i < NUM_SUBJECTS; i++) {
		cin >> student.grades[i];
	}
}
// Function to calculate the average grade for a student
double calc_average(const Student& student) {
	double sum = 0.0;
	for (int i = 0; i < NUM_SUBJECTS; i++) {
		sum += student.grades[i];
	}
	return sum / NUM_SUBJECTS;
}
// Function to display the grades for a student
void display_grades(const Student& student) {
	cout << "the Name of student: " << student.name << endl;
	cout << "the Grades: ";
	for (int i = 0; i < NUM_SUBJECTS; i++) {
		cout << student.grades[i] << " ";
	}
	cout << endl << "the total grades: " << calc_average(student) << endl;
}
// Function to save data to a file
void save_data(const Student students[], const string& filename, int num_students) {
	ofstream out(filename);
	for (int i = 0; i < num_students; i++) {
		out << students[i].name << " ";
		for (int j = 0; j < NUM_SUBJECTS; j++) {
			out << students[i].grades[j] << " ";
		}
		out << endl;
	}
	out.close();
}
// Function to load data from a file
void load_data(Student students[], const string& filename, int num_students) {
	ifstream in(filename);
	int i = 0;
	while (in >> students[i].name) {
		for (int j = 0; j < NUM_SUBJECTS; j++) {
			in >> students[i].grades[j];
		}
		i++;
	}
	num_students = i;
	in.close();
}
void display_menu() {
	cout << "                                                     ======================\n";
	cout << "                                                     Student Grade Tracker\n";
	cout << "                                                     ======================\n";
	cout << "====================\n";
	cout << "1. Add student\n";
	cout << "2. Add student grades\n";
	cout << "3. Display student grades\n";
	cout << "4. Delete student\n";
	cout << "5. Exit application\n";
	cout << "====================\n";
	cout << "Enter your choice:\n====================\n ";
}
int main() {
	int choice;
	char answer;
	int num_students = 0;
	Student students[NUM_STUDENTS];
	string filename = "grades.txt";
	while (true) {
		display_menu();
		cin >> choice;
		switch (choice) {
		case 1:
			if (num_students < NUM_STUDENTS) {
				add_name(students[num_students]);
				num_students++;
			}
			else {
				cout << "maximum number of students reached.\n";
			}
			break;
		case 2:
			if (num_students > 0) {
				string studentName;
				cout << "Enter the student name to insert grades: ";
				cin.ignore();
				getline(cin, studentName);
				bool found = false;
				for (int i = 0; i < num_students; i++) {
					if (students[i].name == studentName) {
						found = true;
						add_grades(students[i]);
						break;
					}
				}
				if (!found) {
					cout << "Student '" << studentName << "' not found.\n";
				}
			}
			else {
				cout << "No students to enter grades.\n";
			}
			break;
		case 3:
		{
			if (num_students > 0) {
				string studentToDisplay;
				cout << "Enter the name of the student to display grades: ";
				cin.ignore();
				getline(cin, studentToDisplay);
				bool found = false;
				for (int i = 0; i < num_students; i++) {
					if (students[i].name == studentToDisplay) {
						found = true;
						display_grades(students[i]);
						break;
					}
				}
				if (!found) {
					cout << "Student '" << studentToDisplay << "' not found.\n";
				}
			}
			else {
				cout << "No students to display.\n";
			}
			break;
		}
		case 4:
			if (num_students > 0) {
				string studentToDelete;
				cout << "Enter the name of the student to delete: ";
				cin.ignore();
				getline(cin, studentToDelete);
				bool found = false;
				for (int i = 0; i < num_students; i++) {
					if (students[i].name == studentToDelete) {
						found = true;
						// Shift remaining students to fill the gap
						for (int j = i; j < num_students - 1; j++) {
							students[j] = students[j + 1];
						}
						num_students--;
						cout << "Student '" << studentToDelete << "' deleted successfully.\n";
						break;
					}
				}
				if (!found) {
					cout << "Student '" << studentToDelete << "' not found.\n";
				}
			}
			else {
				cout << "No students to delete.\n";
			}
			break;
		case 5:
			cout << "do you want to exit?\n if yes...please enter=  y  \n If no.... pleease enter=  n\n enter your choice=";
			cin >> answer;
			if (answer == 'y') {
				save_data(students, filename, num_students);
				cout << "Exiting...\n";
				return 0;
			}
			break;
		default:
			cout << "sorry...Invalid choice. Please try to enter a avilable option.\n";
		}
	}
	Student student[NUM_STUDENTS];
	string filname = "grade.txt";
	// Load data from file
	load_data(students, filename, NUM_STUDENTS);
	// Add grades and display for each student
	for (int i = 0; i < NUM_STUDENTS; i++) {
		add_grades(students[i]);
		display_grades(students[i]);
	}
	// Save data to file
	save_data(students, filename, NUM_STUDENTS);
	return 0;
}
