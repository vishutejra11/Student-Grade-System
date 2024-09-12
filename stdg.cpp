#include<bits/stdc++.h>

using namespace std;

class Student {
public:
    string name;
    int id;
    map<string, int> subjectGrades; 
    double averageGrade;

    Student(string n, int i) : name(n), id(i), averageGrade(0.0) {}

    void addGrade(string subject, int grade) {
        subjectGrades[subject] = grade;
    }

    void editGrade(string subject, int grade) {
        if (subjectGrades.find(subject) != subjectGrades.end()) {
            subjectGrades[subject] = grade;
            cout << "Grade updated for " << name << " in " << subject << "." << endl;
        } else {
            cout << "Subject not found." << endl;
        }
    }

    void displayGrades() {
        cout << "Grades for " << name << " (ID: " << id << "):\n";
        for (const auto &subjectGrade : subjectGrades) {
            cout << subjectGrade.first << ": " << subjectGrade.second << endl;
        }
    }

    double calculateAverage() {
        if (subjectGrades.empty()) return 0.0;
        int sum = 0;
        for (const auto &subjectGrade : subjectGrades) {
            sum += subjectGrade.second;
        }
        averageGrade = static_cast<double>(sum) / subjectGrades.size();
        return averageGrade;
    }
};

class GradeBook {
private:
    vector<Student> students;

public:
    void addStudent(string name, int id) {
        students.push_back(Student(name, id));
    }

    Student* findStudent(int id) {
        for (auto &student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    void addGrade(int id, string subject, int grade) {
        Student* student = findStudent(id);
        if (student) {
            student->addGrade(subject, grade);
        } else {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void editGrade(int id, string subject, int grade) {
        Student* student = findStudent(id);
        if (student) {
            student->editGrade(subject, grade);
        } else {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void deleteStudent(int id) {
        auto it = remove_if(students.begin(), students.end(), [&](Student& student) { return student.id == id; });
        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student with ID " << id << " deleted." << endl;
        } else {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void displayAllGrades() {
        for (Student &student : students) {
            student.displayGrades();
        }
    }

    void calculateAverageForAll() {
        for (Student &student : students) {
            cout << "Average for " << student.name << " (ID: " << student.id << "): " << student.calculateAverage() << endl;
        }
    }

    void displayTopPerformerInSubject(string subject) {
        string topStudent;
        int highestGrade = -1;

        for (Student &student : students) {
            if (student.subjectGrades.find(subject) != student.subjectGrades.end()) {
                if (student.subjectGrades[subject] > highestGrade) {
                    highestGrade = student.subjectGrades[subject];
                    topStudent = student.name;
                }
            }
        }

        if (highestGrade != -1) {
            cout << "Top performer in " << subject << ": " << topStudent << " with " << highestGrade << " marks." << endl;
        } else {
            cout << "No grades available for " << subject << "." << endl;
        }
    }

    void saveToFile(const string &filename) {
        ofstream outFile(filename);
        for (const Student &student : students) {
            outFile << student.name << "," << student.id;
            for (const auto &subjectGrade : student.subjectGrades) {
                outFile << "," << subjectGrade.first << "," << subjectGrade.second;
            }
            outFile << endl;
        }
        outFile.close();
    }

    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name;
            int id;
            map<string, int> grades;

            getline(ss, name, ',');
            ss >> id;
            if (ss.peek() == ',') ss.ignore();

            string subject;
            int grade;
            while (getline(ss, subject, ',') && ss >> grade) {
                grades[subject] = grade;
                if (ss.peek() == ',') ss.ignore();
            }
            Student student(name, id);
            student.subjectGrades = grades;
            students.push_back(student);
        }
        inFile.close();
    }
};

int main() {
    GradeBook gb;
    int choice;

    while (true) {
        cout << "\n1. Add Student\n2. Add Grade\n3. Edit Grade\n4. Delete Student\n5. Display All Grades\n6. Calculate Average for All\n7. Display Top Performer in Subject\n8. Save to File\n9. Load from File\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id;
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter student ID: ";
            cin >> id;
            gb.addStudent(name, id);
        } else if (choice == 2) {
            int id, grade;
            string subject;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter subject: ";
            cin >> subject;
            cout << "Enter grade: ";
            cin >> grade;
            gb.addGrade(id, subject, grade);
        } else if (choice == 3) {
            int id, grade;
            string subject;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter subject: ";
            cin >> subject;
            cout << "Enter new grade: ";
            cin >> grade;
            gb.editGrade(id, subject, grade);
        } else if (choice == 4) {
            int id;
            cout << "Enter student ID to delete: ";
            cin >> id;
            gb.deleteStudent(id);
        } else if (choice == 5) {
            gb.displayAllGrades();
        } else if (choice == 6) {
            gb.calculateAverageForAll();
        } else if (choice == 7) {
            string subject;
            cout << "Enter subject to view top performer: ";
            cin >> subject;
            gb.displayTopPerformerInSubject(subject);
        } else if (choice == 8) {
            gb.saveToFile("students.txt");
        } else if (choice == 9) {
            gb.loadFromFile("students.txt");
        } else if (choice == 10) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
