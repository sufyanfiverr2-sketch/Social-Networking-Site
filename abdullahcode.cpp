#include <iostream>
#include <string>

using namespace std;

class Student {
    string fullName;
    string rollNo;
public:
    Student(string fn = "", string rn = "") : fullName(fn), rollNo(rn) {}
    string getFullName() const { return fullName; }
    string getRollNo()   const { return rollNo; }
};

class Course {
public:
    string title;
    string code;
    int    seats;
    int    seatsFilled;
    Student** studentList;

    Course(string t, string c, int s)
        : title(t), code(c), seats(s), seatsFilled(0) {
        studentList = new Student*[seats];
    }

    ~Course() {
        delete[] studentList;
    }
};

int main() {
    Student p1("Hamza", "EE201");
    Student p2("Sara",  "EE202");
    Student p3("Umar",  "EE203");
    Student* batch[] = { &p1, &p2, &p3 };
    int batchSize = 3;

    Course subj("Data Structures", "CS-301", 2);

    string rollsToEnroll[] = { "EE201", "EE202", "EE203", "EE201", "ME999" };

    for (int i = 0; i < 5; i++) {
        try {
            string currentRoll = rollsToEnroll[i];

            // Find student in batch
            Student* found = nullptr;
            for (int j = 0; j < batchSize; j++) {
                if (batch[j]->getRollNo() == currentRoll) {
                    found = batch[j];
                    break;
                }
            }
            if (!found) throw "Exception: Student record not found";

            // Check duplicate enrollment
            for (int k = 0; k < subj.seatsFilled; k++) {
                if (subj.studentList[k]->getRollNo() == currentRoll)
                    throw "Exception: Student already enrolled in this course";
            }

            // Check capacity
            if (subj.seatsFilled >= subj.seats) {
                string err = "Exception: Course " + subj.title + " is already full";
                throw err;
            }

            // Enroll
            subj.studentList[subj.seatsFilled++] = found;
            cout << found->getFullName() << " enrolled in " << subj.title << endl;

        }
        catch (const char* msg) { cout << msg << endl; }
        catch (string msg)      { cout << msg << endl; }
    }

    cout << "\n--- Course " << subj.title << " Students ---" << endl;
    for (int i = 0; i < subj.seatsFilled; i++) {
        cout << i + 1 << ". " << subj.studentList[i]->getFullName()
             << " (" << subj.studentList[i]->getRollNo() << ")" << endl;
    }

    return 0;
}