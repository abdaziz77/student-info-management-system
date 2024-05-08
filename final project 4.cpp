#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string id;
    string name;
    double cgpa;
    string semester;
};

class StudentManagementSystem {
private:
    vector<Student> students;
    string username;
    string password;

public:
    StudentManagementSystem(string uname, string pwd) : username(uname), password(pwd) {}

    bool login(string uname, string pwd) {
        return (username == uname && password == pwd);
    }

    void addStudent(Student student) {
        students.push_back(student);
    }

    void deleteStudent(string id) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                return;
            }
        }
        cout << "Student with ID " << id << " not found!\n";
    }

    void editStudent(string id, Student updatedStudent) {
        for (auto& student : students) {
            if (student.id == id) {
                student = updatedStudent;
                return;
            }
        }
        cout << "Student with ID " << id << " not found!\n";
    }

    void searchStudent(string id) {
        for (const auto& student : students) {
            if (student.id == id) {
                cout << "Student Information:\n";
                cout << "ID: " << student.id << "\n";
                cout << "Name: " << student.name << "\n";
                cout << "CGPA: " << student.cgpa << "\n";
                cout << "Semester: " << student.semester << "\n";
                return;
            }
        }
        cout << "Student with ID " << id << " not found!\n";
    }

    void displayStudents() {
        cout << "Students Information:\n";
        for (const auto& student : students) {
            cout << "ID: " << student.id << "\n";
            cout << "Name: " << student.name << "\n";
            cout << "CGPA: " << student.cgpa << "\n";
            cout << "Semester: " << student.semester << "\n\n";
        }
    }

    void saveToFile() {
        ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (const auto& student : students) {
                outFile << student.id << "," << student.name << "," << student.cgpa << "," << student.semester << "\n";
            }
            outFile.close();
        } else {
            cout << "Unable to open file for saving!\n";
        }
    }

    void loadFromFile() {
        students.clear();
        ifstream inFile("students.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                Student student;
                size_t pos = line.find(",");
                student.id = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(",");
                student.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(",");
                student.cgpa = stoi(line.substr(0, pos));
                line.erase(0, pos + 1);
                student.semester = line;
                students.push_back(student);
            }
            inFile.close();
        } else {
            cout << "Unable to open file for loading!\n";
        }
    }
};

int main() {
    StudentManagementSystem system("admin", "password");

    // Login
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (system.login(username, password)) {
        cout << "Login successful!\n";

        // Load data from file
        system.loadFromFile();

        double choice;
        do{


    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t 1. Enter New Student Record" << endl;
    cout << "\t\t\t 2. Delete Student Record" << endl;
    cout << "\t\t\t 3. Modify Student Record" << endl;
    cout << "\t\t\t 4. Search Student Record by ID" << endl;
    cout << "\t\t\t 5. Display Student Record" << endl;
    cout << "\t\t\t 6. Save to File" << endl;
    cout << "\t\t\t 7. Exit\n"<< endl;

    cout << "\t\t\t............................" << endl;
    cout << "\t\t\tChoose Options:[1/2/3/4/5/6]" << endl;
    cout << "\t\t\t............................" << endl;
    cout << "Enter Your Choice: ";
    cin >> choice;

            if (choice == 1) {
                Student student;
                cout << "Enter ID: ";
                cin >> student.id;
                cout << "Enter name: ";
                cin >> student.name;
                cout << "Enter cgpa: ";
                cin >> student.cgpa;
                cout << "Enter semester: ";
                cin.ignore(); // clear buffer
                getline(cin, student.semester);
                system.addStudent(student);
            } else if (choice == 2) {
                string id;
                cout << "Enter ID of student to delete: ";
                cin >> id;
                system.deleteStudent(id);
            } else if (choice == 3) {
                string id;
                cout << "Enter ID of student to edit: ";
                cin >> id;
                Student updatedStudent;
                cout << "Enter name: ";
                cin >> updatedStudent.name;
                cout << "Enter cgpa: ";
                cin >> updatedStudent.cgpa;
                cout << "Enter semester: ";
                cin.ignore(); // clear buffer
                getline(cin, updatedStudent.semester);
                system.editStudent(id, updatedStudent);
            } else if (choice == 4) {
                string id;
                cout << "Enter ID of student to search: ";
                cin >> id;
                system.searchStudent(id);
            } else if (choice == 5) {
                system.displayStudents();
            } else if (choice == 6) {
                system.saveToFile();
            } else if (choice == 7) {
                cout << "Exiting...\n";
            } else {
                cout << "Invalid choice!\n";
            }
        } while (choice != 7);
    } else {
        cout << "Invalid username or password!\n";
    }

    return 0;
}
