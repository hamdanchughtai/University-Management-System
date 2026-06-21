//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


struct Course {

    int courseID;
    string name;
    int credits;
    int timeSlot;
};

struct Student {

    string name;
    int id;

    int registeredCourses[10];
    int registeredCount;
};


Course courses[100];
Student students[100];

int courseCount = 0;
int studentCount = 0;

int nextCourseID = 1001;


// Menus
void mainMenu();
void courseMenu();
void studentMenu();
void scheduleMenu();

// Course Functions
void addCourse();
void editCourse();
void dropCourse();
void viewCourses();
void searchCourse();

// Student Functions
void registerStudent();
void editStudent();
void removeStudent();
void viewStudents();
void searchStudent();

// Enrollment Functions
void enrollStudent();
void unenrollStudent();
void viewStudentSchedule();

// Statistics
void systemStatistics();

// File Handling
void saveCoursesToFile();
void loadCoursesFromFile();

void saveStudentsToFile();
void loadStudentsFromFile();

// Helpers
void pauseScreen();
string getSlotName(int slot);
int findCourseIndexByID(int id);


int main() {

    system("color 0B");

    loadCoursesFromFile();
    loadStudentsFromFile();

    mainMenu();

    return 0;
}


void pauseScreen() {

    cin.ignore();

    cout << "\nPress Enter to continue...";
    cin.get();
}

string getSlotName(int slot) {

    if(slot == 1)
        return "Morning";

    else if(slot == 2)
        return "Afternoon";

    else if(slot == 3)
        return "Evening";

    else
        return "Unknown";
}

int findCourseIndexByID(int id) {

    for(int i=0; i<courseCount; i++) {

        if(courses[i].courseID == id) {

            return i;
        }
    }

    return -1;
}


void mainMenu() {

    int choice;

    while(true) {

        system("cls");

        cout << "====================================================\n";
        cout << "          UNIVERSITY MANAGEMENT SYSTEM\n";
        cout << "====================================================\n";

        cout << "1. Course Management\n";
        cout << "2. Student Management\n";
        cout << "3. Schedule Management\n";
        cout << "4. System Statistics\n";
        cout << "5. Exit\n";

        cout << "====================================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid Input!\n";

            pauseScreen();

            continue;
        }

        if(choice == 1) {

            courseMenu();
        }

        else if(choice == 2) {

            studentMenu();
        }

        else if(choice == 3) {

            scheduleMenu();
        }

        else if(choice == 4) {

            systemStatistics();
        }

        else if(choice == 5) {

            saveCoursesToFile();
            saveStudentsToFile();

            cout << "\nSaving Data...\n";
            cout << "Thank You For Using The System!\n";

            break;
        }

        else {

            cout << "\nInvalid Choice!\n";

            pauseScreen();
        }
    }
}

//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void courseMenu() {

    int choice;

    while(true) {

        system("cls");

        cout << "================ COURSE MANAGEMENT ================\n";

        cout << "1. Add Course\n";
        cout << "2. Edit Course\n";
        cout << "3. Remove Course\n";
        cout << "4. View Courses\n";
        cout << "5. Search Course\n";
        cout << "6. Back\n";

        cout << "===================================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {

            addCourse();
        }

        else if(choice == 2) {

            editCourse();
        }

        else if(choice == 3) {

            dropCourse();
        }

        else if(choice == 4) {

            viewCourses();
            pauseScreen();
        }

        else if(choice == 5) {

            searchCourse();
            pauseScreen();
        }

        else if(choice == 6) {

            break;
        }

        else {

            cout << "\nInvalid Choice!\n";

            pauseScreen();
        }
    }
}
//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void addCourse() {

    system("cls");

    if(courseCount >= 100) {

        cout << "Course Limit Reached!\n";

        pauseScreen();

        return;
    }

    cin.ignore();

    courses[courseCount].courseID = nextCourseID++;

    cout << "Enter Course Name: ";
    getline(cin, courses[courseCount].name);

    cout << "Enter Credit Hours: ";

    while(!(cin >> courses[courseCount].credits)) {

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Input! Enter Again: ";
    }

    cout << "\nSelect Time Slot\n";
    cout << "1. Morning\n";
    cout << "2. Afternoon\n";
    cout << "3. Evening\n";

    cout << "Choice: ";

    while(!(cin >> courses[courseCount].timeSlot)) {

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Input! Enter Again: ";
    }

    courseCount++;

    cout << "\nCourse Added Successfully!\n";

    pauseScreen();
}
//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void editCourse() {

    system("cls");

    viewCourses();

    int id;

    cout << "\nEnter Course ID To Edit: ";
    cin >> id;

    int index = findCourseIndexByID(id);

    if(index == -1) {

        cout << "Course Not Found!\n";

        pauseScreen();

        return;
    }

    cin.ignore();

    cout << "\nEnter New Course Name: ";
    getline(cin, courses[index].name);

    cout << "Enter New Credits: ";
    cin >> courses[index].credits;

    cout << "\nSelect New Time Slot\n";
    cout << "1. Morning\n";
    cout << "2. Afternoon\n";
    cout << "3. Evening\n";

    cout << "Choice: ";
    cin >> courses[index].timeSlot;

    cout << "\nCourse Updated Successfully!\n";

    pauseScreen();
}
//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void dropCourse() {

    system("cls");

    viewCourses();

    int id;

    cout << "\nEnter Course ID To Remove: ";
    cin >> id;

    int index = findCourseIndexByID(id);

    if(index == -1) {

        cout << "Course Not Found!\n";

        pauseScreen();

        return;
    }


    for(int i=0; i<studentCount; i++) {

        for(int j=0; j<students[i].registeredCount; j++) {

            if(students[i].registeredCourses[j] == id) {

                for(int k=j; k<students[i].registeredCount-1; k++) {

                    students[i].registeredCourses[k] =
                    students[i].registeredCourses[k+1];
                }

                students[i].registeredCount--;
                j--;
            }
        }
    }


    for(int i=index; i<courseCount-1; i++) {

        courses[i] = courses[i+1];
    }

    courseCount--;

    cout << "\nCourse Removed Successfully!\n";

    pauseScreen();
}


void viewCourses() {

    system("cls");

    if(courseCount == 0) {

        cout << "No Courses Available!\n";

        return;
    }

    cout << left
         << setw(10) << "Index"
         << setw(15) << "Course ID"
         << setw(25) << "Course Name"
         << setw(10) << "Credits"
         << setw(15) << "Timing"
         << endl;

    cout << "-----------------------------------------------------------------\n";

    for(int i=0; i<courseCount; i++) {

        cout << left
             << setw(10) << i
             << setw(15) << courses[i].courseID
             << setw(25) << courses[i].name
             << setw(10) << courses[i].credits
             << setw(15) << getSlotName(courses[i].timeSlot)
             << endl;
    }
}


void searchCourse() {

    system("cls");

    cin.ignore();

    string name;

    cout << "Enter Course Name To Search: ";
    getline(cin, name);

    bool found = false;

    for(int i=0; i<courseCount; i++) {

        if(courses[i].name == name) {

            found = true;

            cout << "\nCourse Found!\n";

            cout << "Course ID : " << courses[i].courseID << endl;
            cout << "Credits   : " << courses[i].credits << endl;
            cout << "Timing    : "
                 << getSlotName(courses[i].timeSlot)
                 << endl;
        }
    }

    if(!found) {

        cout << "\nCourse Not Found!\n";
    }
}

//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System
void studentMenu() {

    int choice;

    while(true) {

        system("cls");

        cout << "================ STUDENT MANAGEMENT ================\n";

        cout << "1. Register Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Remove Student\n";
        cout << "4. View Students\n";
        cout << "5. Search Student\n";
        cout << "6. Enroll Student In Course\n";
        cout << "7. Unenroll Student From Course\n";
        cout << "8. Back\n";

        cout << "====================================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {

            registerStudent();
        }

        else if(choice == 2) {

            editStudent();
        }

        else if(choice == 3) {

            removeStudent();
        }

        else if(choice == 4) {

            viewStudents();
            pauseScreen();
        }

        else if(choice == 5) {

            searchStudent();
            pauseScreen();
        }

        else if(choice == 6) {

            enrollStudent();
        }

        else if(choice == 7) {

            unenrollStudent();
        }

        else if(choice == 8) {

            break;
        }

        else {

            cout << "\nInvalid Choice!\n";

            pauseScreen();
        }
    }
}


//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void registerStudent() {

    system("cls");

    if(studentCount >= 100) {

        cout << "Student Limit Reached!\n";

        pauseScreen();

        return;
    }

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, students[studentCount].name);

    cout << "Enter Student ID: ";

    while(!(cin >> students[studentCount].id)) {

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Input! Enter Again: ";
    }


    for(int i=0; i<studentCount; i++) {

        if(students[i].id ==
           students[studentCount].id) {

            cout << "\nStudent ID Already Exists!\n";

            pauseScreen();

            return;
        }
    }

    students[studentCount].registeredCount = 0;

    studentCount++;

    cout << "\nStudent Registered Successfully!\n";

    pauseScreen();
}


void editStudent() {

    system("cls");

    viewStudents();

    int index;

    cout << "\nEnter Student Index To Edit: ";
    cin >> index;

    if(index < 0 || index >= studentCount) {

        cout << "Invalid Student!\n";

        pauseScreen();

        return;
    }

    cin.ignore();

    cout << "\nEnter New Name: ";
    getline(cin, students[index].name);

    cout << "Enter New Student ID: ";
    cin >> students[index].id;

    cout << "\nStudent Updated Successfully!\n";

    pauseScreen();
}

//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System


void removeStudent() {

    system("cls");

    viewStudents();

    int index;

    cout << "\nEnter Student Index To Remove: ";
    cin >> index;

    if(index < 0 || index >= studentCount) {

        cout << "Invalid Student!\n";

        pauseScreen();

        return;
    }

    for(int i=index; i<studentCount-1; i++) {

        students[i] = students[i+1];
    }

    studentCount--;

    cout << "\nStudent Removed Successfully!\n";

    pauseScreen();
}


void viewStudents() {

    system("cls");

    if(studentCount == 0) {

        cout << "No Students Registered!\n";

        return;
    }

    cout << left
         << setw(10) << "Index"
         << setw(25) << "Student Name"
         << setw(15) << "Student ID"
         << setw(10) << "Courses"
         << endl;

    cout << "-------------------------------------------------------------\n";

    for(int i=0; i<studentCount; i++) {

        cout << left
             << setw(10) << i
             << setw(25) << students[i].name
             << setw(15) << students[i].id
             << setw(10) << students[i].registeredCount
             << endl;
    }
}


void searchStudent() {

    system("cls");

    int id;

    cout << "Enter Student ID To Search: ";
    cin >> id;

    bool found = false;

    for(int i=0; i<studentCount; i++) {

        if(students[i].id == id) {

            found = true;

            cout << "\nStudent Found!\n";

            cout << "Name : " << students[i].name << endl;
            cout << "Courses Registered : "
                 << students[i].registeredCount
                 << endl;
        }
    }

    if(!found) {

        cout << "\nStudent Not Found!\n";
    }
}


//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void enrollStudent() {

    system("cls");

    viewStudents();

    int sIndex;

    cout << "\nEnter Student Index: ";
    cin >> sIndex;

    if(sIndex < 0 || sIndex >= studentCount) {

        cout << "Invalid Student!\n";

        pauseScreen();

        return;
    }

    if(students[sIndex].registeredCount >= 10) {

        cout << "Maximum Course Limit Reached!\n";

        pauseScreen();

        return;
    }

    viewCourses();

    int courseID;

    cout << "\nEnter Course ID: ";
    cin >> courseID;

    int cIndex = findCourseIndexByID(courseID);

    if(cIndex == -1) {

        cout << "Course Not Found!\n";

        pauseScreen();

        return;
    }


    for(int i=0; i<students[sIndex].registeredCount; i++) {

        if(students[sIndex].registeredCourses[i] ==
           courseID) {

            cout << "\nStudent Already Enrolled In This Course!\n";

            pauseScreen();

            return;
        }
    }


    for(int i=0; i<students[sIndex].registeredCount; i++) {

        int existingID =
        students[sIndex].registeredCourses[i];

        int existingIndex =
        findCourseIndexByID(existingID);

        if(existingIndex != -1) {

            if(courses[existingIndex].timeSlot ==
               courses[cIndex].timeSlot) {

                cout << "\nSchedule Conflict Detected!\n";

                pauseScreen();

                return;
            }
        }
    }

    students[sIndex]
    .registeredCourses[students[sIndex].registeredCount]
    = courseID;

    students[sIndex].registeredCount++;

    cout << "\nEnrollment Successful!\n";

    pauseScreen();
}


//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void unenrollStudent() {

    system("cls");

    viewStudents();

    int sIndex;

    cout << "\nEnter Student Index: ";
    cin >> sIndex;

    if(sIndex < 0 || sIndex >= studentCount) {

        cout << "Invalid Student!\n";

        pauseScreen();

        return;
    }

    if(students[sIndex].registeredCount == 0) {

        cout << "Student Has No Courses!\n";

        pauseScreen();

        return;
    }

    cout << "\nRegistered Courses:\n";

    for(int i=0; i<students[sIndex].registeredCount; i++) {

        int courseID =
        students[sIndex].registeredCourses[i];

        int index =
        findCourseIndexByID(courseID);

        if(index != -1) {

            cout << courses[index].courseID
                 << " - "
                 << courses[index].name
                 << endl;
        }
    }

    int removeID;

    cout << "\nEnter Course ID To Remove: ";
    cin >> removeID;

    bool found = false;

    for(int i=0; i<students[sIndex].registeredCount; i++) {

        if(students[sIndex].registeredCourses[i]
           == removeID) {

            found = true;

            for(int j=i;
                j<students[sIndex].registeredCount-1;
                j++) {

                students[sIndex].registeredCourses[j]
                =
                students[sIndex].registeredCourses[j+1];
            }

            students[sIndex].registeredCount--;

            cout << "\nCourse Removed Successfully!\n";

            break;
        }
    }

    if(!found) {

        cout << "\nCourse Not Found!\n";
    }

    pauseScreen();
}


void scheduleMenu() {

    int choice;

    while(true) {

        system("cls");

        cout << "================ SCHEDULE MANAGEMENT ================\n";

        cout << "1. View Student Schedule\n";
        cout << "2. Back\n";

        cout << "=====================================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {

            viewStudentSchedule();
            pauseScreen();
        }

        else if(choice == 2) {

            break;
        }

        else {

            cout << "\nInvalid Choice!\n";

            pauseScreen();
        }
    }
}


//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void viewStudentSchedule() {

    system("cls");

    viewStudents();

    int sIndex;

    cout << "\nEnter Student Index: ";
    cin >> sIndex;

    if(sIndex < 0 || sIndex >= studentCount) {

        cout << "Invalid Student!\n";

        return;
    }

    cout << "\nSchedule For "
         << students[sIndex].name
         << ":\n";

    int totalCredits = 0;

    for(int i=0; i<students[sIndex].registeredCount; i++) {

        int courseID =
        students[sIndex].registeredCourses[i];

        int cIndex =
        findCourseIndexByID(courseID);

        if(cIndex != -1) {

            cout << "- "
                 << courses[cIndex].name
                 << " | "
                 << getSlotName(courses[cIndex].timeSlot)
                 << " | Credits: "
                 << courses[cIndex].credits
                 << endl;

            totalCredits +=
            courses[cIndex].credits;
        }
    }

    cout << "\nTotal Credits: "
         << totalCredits
         << endl;
}


void systemStatistics() {

    system("cls");

    int totalEnrollments = 0;

    for(int i=0; i<studentCount; i++) {

        totalEnrollments +=
        students[i].registeredCount;
    }

    cout << "====================================================\n";
    cout << "                 SYSTEM STATISTICS\n";
    cout << "====================================================\n";

    cout << "Total Students     : "
         << studentCount
         << endl;

    cout << "Total Courses      : "
         << courseCount
         << endl;

    cout << "Total Enrollments  : "
         << totalEnrollments
         << endl;

    cout << "====================================================\n";

    pauseScreen();
}


void saveCoursesToFile() {

    ofstream file("courses.txt");

    for(int i=0; i<courseCount; i++) {

        file << courses[i].courseID << endl;
        file << courses[i].name << endl;
        file << courses[i].credits << endl;
        file << courses[i].timeSlot << endl;
    }

    file.close();
}


void loadCoursesFromFile() {

    ifstream file("courses.txt");

    if(!file) {

        return;
    }

    while(file >> courses[courseCount].courseID) {

        file.ignore();

        getline(file, courses[courseCount].name);

        file >> courses[courseCount].credits;
        file >> courses[courseCount].timeSlot;

        if(courses[courseCount].courseID >=
           nextCourseID) {

            nextCourseID =
            courses[courseCount].courseID + 1;
        }

        courseCount++;
    }

    file.close();
}


//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System

void saveStudentsToFile() {

    ofstream file("students.txt");

    for(int i=0; i<studentCount; i++) {

        file << students[i].name << endl;
        file << students[i].id << endl;
        file << students[i].registeredCount << endl;

        for(int j=0;
            j<students[i].registeredCount;
            j++) {

            file << students[i]
            .registeredCourses[j]
            << endl;
        }
    }

    file.close();
}


void loadStudentsFromFile() {

    ifstream file("students.txt");

    if(!file) {

        return;
    }

    while(getline(file, students[studentCount].name)) {

        file >> students[studentCount].id;

        file >> students[studentCount]
        .registeredCount;

        for(int j=0;
            j<students[studentCount].registeredCount;
            j++) {

            file >> students[studentCount]
            .registeredCourses[j];
        }

        file.ignore();

        studentCount++;
    }

    file.close();
}

//Made By Hamdan Chughtai
//https://github.com/hamdanchughtai/University-Management-System