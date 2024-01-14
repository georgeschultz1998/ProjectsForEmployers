/*
Assignment 4 main.cpp
Student: Anthony Schultz vt7482
*/

#include <algorithm> // Include this header for remove and replace functions
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Student {
public:
  string firstName;
  string lastName;
  float programGrade[6];
  float testGrade[4];
  float finalExamGrade;
  float grade;
  float avgProgramGrade;
  float avgTestGrade;
  float totalProgramGrade;
  float totalTestGrade;
  float TotalFinalGrade;
  float finalGrade;
  int studNumber;
  char lastNameLetter;

private:
};

int gradeValue(string) {
  if ("A")
    return 5;
  if ("B")
    return 4;
  if ("C")
    return 3;
  if ("D")
    return 2;
  if ("F")
    return 1;
}
// create an array of students
Student stud[9999];
string inputName = "GradesInput.csv";
string outputName = "Grades.out";
string outputName2 = "Grades.dat";
bool programGraded[7];
bool testGraded[5];
bool finalGraded[2];
char gradeType;

class commands {
private:
  // int studNumber=1;
  // For testing purposes!!! -------------- -------------- --------------
  // --------------
  int programCount = 1, finalCount = 1, testCount = 1;
  int programNum = 1;
  int testNum;
  int studentNumber = 1;
  int studentCount = 0;
  float programWeight = 33, testWeight = 33, finalWeight = 34, totalWeight;
  float avgProgramGrade = 0.0;
  float avgTestGrade = 0.0;
  string programAssignment;
  string studentFirstName, studentLastName;
  string studentGrade[0];

public:
  char userAnswer;
  char userAnswer2;
  void setUp();
  void addStudent();
  void readGradesDat();
  void recordProgramGrade();
  void recordTestGrade();
  void recordFinalGrade();
  void changeGrade();
  void calculateFinalGrade();
  void outputGrades();
  int findStudentByNum(int num);
  int findStudentByLastName(string name);
  void save();
};

// Function to read Grades.dat file and save all data.
inline void commands::readGradesDat() {
  ifstream inputFile(inputName);
  string line, value;

  if (!inputFile) {
    cerr << "Error opening file: " << inputName << endl;
    return;
  }

  // Skipping the header line
  getline(inputFile, line);

  studentCount = 0; // Reset student count

  // Process each student's data
  while (getline(inputFile, line)) {
    stringstream ss(line);

    // Read student number
    getline(ss, value, ',');
    stud[studentCount].studNumber = stoi(value);

    // Read first name
    getline(ss, value, ',');
    stud[studentCount].firstName = value;

    // Read last name
    getline(ss, value, ',');
    stud[studentCount].lastName = value;

    // Read programming assignment grade
    getline(ss, value, ',');
    stud[studentCount].programGrade[0] =
        stof(value); // Assuming one program grade

    // Read test grade
    getline(ss, value, ',');
    stud[studentCount].testGrade[0] = stof(value); // Assuming one test grade

    // Read final exam grade
    getline(ss, value, ',');
    stud[studentCount].finalExamGrade = stof(value);

    studentCount++; // Increment student count
  }

  inputFile.close();
}

//-----------------------------------------------------------------------------------------
// Function to set up the number of assignments, tests, and finals.
// Also sets up the grade weight for each category.
inline void commands::setUp() {
  while (userAnswer2 != 'M') {
    cout << "------------------------------------------------------------------"
            "------------------------\n";
    cout << "Instructions:\n";
    cout << "Enter '1' to update number of assignments, tests, & finals\n";
    cout << "Enter '2' to update weights assignments, tests, & finals\n";
    cout << "Enter '3' to display current number of assignments and their "
            "weights\n";
    cout << "Enter 'M' to return to main menu.\n";
    cout << "------------------------------------------------------------------"
            "------------------------\n";
    cout << "Enter choice here: ";
    cin >> userAnswer2;
    userAnswer2 = toupper(userAnswer2);

    // Ensures user response is valid
    while (userAnswer2 != '1' && userAnswer2 != '2' && userAnswer2 != '3' &&
           userAnswer2 != 'M') {
      cout << "Invalid Response, must enter '1', '2', '3', or 'M'\n";
      cout << "Enter choice here: ";
      cin >> userAnswer2;
    }

    // Gets the number of programming assignments, tests, and finals
    if (userAnswer2 == '1') {
      cout << "----------------------------------------------------------------"
              "--------------------------\n";
      cout << "Instructions:\n";
      cout << "Enter the number of programming assignments, tests, and "
              "finals.\n";
      cout << "Note: Acceptable range for number of programming assignments is "
              "0 to 6.\n";
      cout << "Note: Acceptable range for number of  tests is 0 to 4.\n";
      cout << "Note: Acceptable range for finals is 0 to 1.\n";
      cout << "----------------------------------------------------------------"
              "--------------------------\n";
      // Gets the number of programming assignments and ensures it is in proper
      // range.
      cout << "Enter the number of programming assignments: ";
      cin >> programCount;
      while (programCount < 0 || programCount > 6) {
        cout << "Number entered is not in acceptable range (0 to 6). Try "
                "again.\n";
        cin >> programCount;
      }

      // Gets the number of tests and ensures it is in proper range.
      cout << "Enter the number of tests: ";
      cin >> testCount;
      while (testCount < 0 || testCount > 4) {
        cout << "Number entered is not in acceptable range(0 to 4). Try "
                "again.\n";
        cin >> testCount;
      }

      // Gets the number of finals and ensures it is in proper range.
      cout << "Enter the number of finals: ";
      cin >> finalCount;
      while (finalCount < 0 || finalCount > 1) {
        cout << "Number entered is not in acceptable range (0 to 1). Try "
                "again.\n";
        cin >> finalCount;
      }
    }
    if (userAnswer2 == '2') {
      cout << "----------------------------------------------------------------"
              "--------------------------\n";
      cout << "Instructions:\n";
      cout << "Enter the weights for programming assignments, tests, and the "
              "final.\n";
      cout << "Note: Total weight calculated by adding together all weights "
              "must equal 100%.\n";
      cout << "Note: A weight must be entered as a whole number such as '33' "
              "for 33%.\n";
      cout << "----------------------------------------------------------------"
              "--------------------------\n";

      // Gets the weights for programming assignments, tests, and final.
      cout << "What is the weight of programming assignments? \n";
      cin >> programWeight;
      cout << "What is the weight of tests?\n";
      cin >> testWeight;
      cout << "What are the weight of final?\n";
      cin >> finalWeight;
      totalWeight = programWeight + testWeight + finalWeight;

      totalWeight = programWeight + testWeight + finalWeight;
      while (totalWeight != 100) {
        cout << "Total weight is " << totalWeight
             << ". Due to that not being 100, you must reenter the weights.\n";
        cout << "What is the weight of programming assignments? \n";
        cin >> programWeight;
        cout << "What is the weight of tests?\n";
        cin >> testWeight;
        cout << "What are the weight of final?\n";
        cin >> finalWeight;
        totalWeight = programWeight + testWeight + finalWeight;
      }
    }

    if (userAnswer2 == '3') {
      cout << "Current number of programming assignments is: " << programCount
           << "\n";
      cout << "Current weight of programming assignments category is: "
           << programWeight << "\n";

      cout << "Current number of tests is: " << testCount << "\n";
      cout << "Current weight of test category is: " << testWeight << "\n";

      cout << "Current number of finals is: " << finalCount << "\n";
      cout << "Current weight of final category is: " << finalWeight << "\n";
    }
  }
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Function to add student to database
inline void commands::addStudent() {
  cout << "--------------------------------------------------------------------"
          "----------------------\n";
  cout << "Instructions: \n";
  cout << "Enter student first name, last name, and student number. \n";
  cout << "Note: student name must be less than 20 characters\n";
  // cout << "Note: student number must be in the range of 1 to 9999\n";
  cout << "--------------------------------------------------------------------"
          "----------------------\n";

  cout << "Enter student first name: ";
  cin >> studentFirstName;
  while (studentFirstName.length() > 20) {
    cout << "Length of first name exceeds 20 characters. Try again.\n";
    cin >> studentFirstName;
  }

  cout << "Enter student last name: ";
  cin >> studentLastName;
  while (studentLastName.length() > 20) {
    cout << "Length of first name exceeds 20 characters. Try again.\n";
    cin >> studentLastName;
  }
  // remove this
  cout << "Enter student number: ";
  cin >> studentNumber;
  while (studentNumber > 9999 || studentNumber < 1) {
    // studentNumber
    cout << "Student number is outside of range of 1 to 9999. Try again. \n";
    cin >> studentNumber;
    cout << "Number= " << studentNumber << endl;
  }

  stud[studentCount].firstName = studentFirstName;
  stud[studentCount].lastName = studentLastName;
  stud[studentCount].studNumber = studentNumber;

  // debug output code can be removed
  cout << "Student name: " << stud[studentCount].firstName << " "
       << stud[studentCount].lastName
       << "\nStudent number: " << stud[studentCount].studNumber << '\n';

  studentCount++; // number of students
  cout << "Current Student Count " << studentCount << endl;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Assignment to record the programming assinment grades.
inline void commands::recordProgramGrade() {
  cout << "--------------------------------------------------------------------"
          "----------------------\n";
  cout << "Instructions: \n";
  cout << "Enter the programming assignment number. \n";
  cout << "Enter the grades for each student. \n";
  cout << "Note: Set up must be completed first. \n";
  cout << "Note: Number of programming assignment must be in range 1 to 6.\n";
  cout << "--------------------------------------------------------------------"
          "----------------------\n";

  if (studentCount < 1) {
    cout << "\nERROR: No student has not been added yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (programCount == -1) {
    cout << "\nERROR: Number of program assignments have not been entered "
            "yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (programCount == 0) {
    cout << "\nERROR: There are " << programCount
         << " programming assignments in this course. No grades to enter.\n";
    return;
  }

  cout << "What is the assignment number?";
  cin >> programNum;

  while (programNum < 1 || programNum > programCount) {
    cout << "Invalid entry. User must enter valid assignment number (1 to "
         << programCount << ").\n";
    cout << "Enter here:";
    cin >> programNum;
  }
  cout << "programNum=" << programNum << endl;

  if (programGraded[programNum - 1]) {
    cout << "Grades for this assignment have already been graded. \n";
    cout << "To update the value of individual student grade, go to 'C' in "
            "menu (change grade). \n";
    return;
  }

  for (int i = 0; i < studentCount; i++) {
    cout << "Enter Grade (0-100) For " << stud[i].lastName << ", "
         << stud[i].firstName << ":";
    cin >> stud[i].programGrade[programNum - 1];

    while (stud[i].programGrade[programNum - 1] < 0 ||
           stud[i].programGrade[programNum - 1] > 100) {
      cout << "\nError, acceptable grade range is 0 to 100.\n";
      cout << "Enter Grade (0-100) For " << stud[i].lastName << " "
           << stud[i].firstName << ":";
      cin >> stud[i].programGrade[programNum - 1];
    }
  }

  programGraded[programNum - 1] = true;
}

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Function to record the test grades for students.
//-----------------------------------------------------------------------------------------
inline void commands::recordTestGrade() {
  cout << "--------------------------------------------------------------------"
          "----------------------\n";
  cout << "Instructions: \n";
  cout << "Enter the test number. \n";
  cout << "Enter the grades for each student. \n";
  cout << "--------------------------------------------------------------------"
          "----------------------\n";

  cout << "What is the test number? \n";
  cout << "Enter here:";

  if (studentCount < 1) {
    cout << "\nERROR: No student has not been added yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (testCount == -1) {
    cout << "\n ERROR: Number of tests have not been entered yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (testCount == 0) {
    cout << "\nERROR: There is " << testCount
         << " tests in this course. No grades to enter.\n";
    return;
  }

  cin >> testNum;
  while (testNum < 1 || testNum > testCount) {
    cout << "Invalid entry. User must enter valid test number (1 to "
         << testCount << ".\n";
    cout << "Enter here:";
    cin >> testNum;
  }

  if (testGraded[testNum] == true) {
    cout << "Grades for this test has already been graded. \n";
    cout << "To update value of individual student grade, go to C in "
            "menu(change grade). \n";
    return;
  }

  if (testGraded[testNum] == 0 && testNum <= testCount) {
    for (int i = 0; i < studentCount; i++) {
      cout << "Enter Grade(0-100) For " << stud[i].lastName << " "
           << stud[i].firstName << ":";
      cin >> stud[i].testGrade[testNum];
      while (stud[i].testGrade[programNum] < 0 ||
             stud[i].testGrade[programNum] > 100) {
        cout << "\nError, acceptable grade range is 0 to 100.\n";
        cout << "Enter Grade(0-100) For " << stud[i].lastName << " "
             << stud[i].firstName << ":";
        cin >> stud[i].testGrade[programNum];
      }
    }
    testGraded[testNum] = true;
    return;
  }
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
inline void commands::recordFinalGrade() {
  cout << "--------------------------------------------------------------------"
          "----------------------\n";
  cout << "Instructions: \n";
  cout << "Enter the final exam grades for each student. \n";
  cout << "--------------------------------------------------------------------"
          "----------------------\n";

  if (studentCount < 1) {
    cout << "\nERROR: No student has not been added yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (finalCount == -1) {
    cout << "\nERROR: Number of finals have not been entered yet.\n";
    cout << "User must do that first through 'S' (set up) in main menu.\n";
    return;
  }

  if (finalCount == 0) {
    cout << "\nERROR: There is " << finalCount
         << " finals in this course. No grades to enter.\n";
    return;
  }

  if (finalGraded[1] == true) {
    cout << "Grades for final has already been graded. \n";
    cout << "To update value of individual student grade, go to C in "
            "menu(change grade). \n";
    return;
  }

  if (finalGraded[1] == false) {
    for (int i = 0; i < studentCount; i++) {
      cout << "Enter Grade (0-100) For " << stud[i].lastName << " "
           << stud[i].firstName << ":";
      cin >> stud[i].finalExamGrade;
      while (stud[i].finalExamGrade < 0 || stud[i].finalExamGrade > 100) {
        cout << "Error, acceptable grade range is 0 to 100.\n";
        cout << "Enter Grade For " << stud[i].lastName << " "
             << stud[i].firstName << ":";
        cin >> stud[i].finalExamGrade;
      }
    }
    finalGraded[1] = true;
  }
}

// -------------------------------------------
inline int commands::findStudentByNum(int num) {
  int snum = -1;
  bool found = false;
  for (int i = 0; i < studentCount; i++) {
    // cout<< "debug change : " << stud[i].studNumber<<endl;
    if (stud[i].studNumber == studentNumber) {
      snum = i;
      found = true;
      break;
    }
  }
  return snum;
}

inline int commands::findStudentByLastName(string name) {
  int snum = -1;
  bool found = false;
  for (int i = 0; i < studentCount; i++) {
    // cout<< "debug change : " << stud[i].studNumber<<endl;
    if (stud[i].lastName == name) {
      snum = i;
      found = true;
      break;
    }
  }
  return snum;
  return -1;
}
// Change grade of student
inline void commands::changeGrade() {
  cout << "--------------------------------------------------------------------"
          "----------------------\n";
  cout << "Instructions: \n";
  cout << "Enter the student number, type of grade, assignment number, and new "
          "grade.\n";
  cout << "--------------------------------------------------------------------"
          "----------------------\n";

  cout << "Enter student number here:";
  cin >> studentNumber;

  cout << "Type of grade input options:\n ";
  cout << "Enter 'P' for programming assignment \n ";
  cout << "Enter 'T' for test \n ";
  cout << "Enter 'F' for Final \n ";
  cin >> gradeType;
  gradeType = toupper(gradeType);

  while (gradeType != 'P' && gradeType != 'T' && gradeType != 'F') {
    cout << "Invalid input. Possible options are 'P', 'T', or 'F'. Try again.";
    cout << "Enter here:";
    cin >> gradeType;
    gradeType = toupper(gradeType);
  }

  if (gradeType == 'P') {
    if (programCount == -1) {
      cout << "Number of program assignments have not been entered yet.\n";
      cout << "User must do that first through 'S' (set up) in main menu.\n";
      return;
    }

    //-------------------------------
    // If user answer = programming assignment
    if (programCount == 0) {
      cout << "There is " << programCount
           << " programming assignments in this course. No grades to enter.\n";
      return;
    }

    cout << "There are " << programCount
         << " programming assignments available for grade changing\n";
    cout << "Which one did you want to change grade for? \n";
    cout << "Enter here:";
    cin >> programNum;
    while (programNum < 1 || programNum > programCount) {
      cout << "Invalid entry. User must enter valid assignment number (1 to "
           << programCount << ").\n";
      cout << "Enter here:";
      cin >> programNum;
    }
    // find the student with number studentNumber

    int snum = findStudentByNum(studentNumber);
    if (snum >= 0) {
      cout << "Enter Grade For " << stud[snum].lastName << " "
           << stud[snum].firstName << ":";

      cin >> stud[snum].programGrade[programNum];
      while (stud[snum].programGrade[programNum] < 0 ||
             stud[snum].programGrade[programNum] > 100) {
        cout << "\nError, acceptable grade range is 0 to 100.\n";
        cout << "Enter Grade For " << stud[snum].lastName << " "
             << stud[snum].firstName << ":";
        cin >> stud[snum].programGrade[programNum];
      }
      cout << "Updated grade for programming assignment " << programNum
           << " for student " << stud[snum].firstName << " "
           << stud[snum].lastName
           << " is:" << stud[snum].programGrade[programNum] << "\n";
    } else {
      cout << "student not found: " << studentNumber << endl;
    }
  }

  //-------------------------------
  // If user answer = test
  if (gradeType == 'T') {
    if (testCount == -1) {
      cout << "Number of test have not been entered yet.\n";
      cout << "User must do that first through 'S' (set up) in main menu.\n";
      return;
    }

    if (testCount == 0) {
      cout << "There is " << testCount
           << " tests in this course. No grades to enter.\n";
      return;
    }

    cout << "There are " << testCount
         << " tests available for grade changing\n";
    cout << "Which one did you want to change grade for? \n";
    cout << "Enter here:";
    cin >> testNum;
    while (testNum < 1 || testNum > testCount) {
      cout << "Invalid entry. User must enter valid assignment number (1 to "
           << testCount << ").\n";
      cout << "Enter here:";
      cin >> testNum;
    }

    // find the student with number studentNumber
    int snum = findStudentByNum(studentNumber);
    if (snum >= 0) {
      cout << "Enter updated Grade(0-100) For: " << stud[snum].firstName << " "
           << stud[snum].lastName << ": ";
      cin >> stud[snum].testGrade[testNum];
      while (stud[snum].testGrade[testNum] < 0 ||
             stud[snum].testGrade[testNum] > 100) {
        cout << "\nError, acceptable grade range is 0 to 100.\n";
        cout << "Enter Grade For " << stud[snum].firstName << " "
             << stud[snum].lastName << ":";
        cin >> stud[snum].testGrade[testNum];
      }
      cout << "Updated grade for test  " << testNum << " for student "
           << stud[snum].firstName << " " << stud[snum].lastName
           << " is:" << stud[snum].testGrade[testNum] << "\n";
    } else {
      cout << "student not found: " << studentNumber << endl;
    }
  }

  // If user answer = final
  if (gradeType == 'F') {
    if (finalCount == -1) {
      cout << "Number of final have not been entered yet.\n";
      cout << "User must do that first through 'S' (set up) in main menu.\n";
      return;
    }

    if (finalCount == 0) {
      cout << "There is " << finalCount
           << " final in this course. No grades to enter.\n";
      return;
    }

    // find the student with number studentNumber
    int snum = findStudentByNum(finalCount);
    if (snum >= 0) {
      cout << "Enter updated Grade (0-100) For: " << stud[snum].firstName << " "
           << stud[snum].lastName << ": ";
      cin >> stud[snum].finalGrade;
      while (stud[snum].finalGrade < 0 || stud[snum].finalGrade > 100) {
        cout << "\nError, acceptable grade range is 0 to 100.\n";
        cout << "Enter Grade For (0-100) " << stud[snum].firstName << " "
             << stud[snum].lastName << ":";
        cin >> stud[snum].finalGrade;
      }
      cout << "Updated grade for the final for student " << stud[snum].firstName
           << " " << stud[snum].lastName << " is:" << stud[snum].finalGrade
           << "\n";
    } else {
      cout << "student not found: " << studentNumber << endl;
    }
  }

  ofstream outputFile(inputName);
  if (!outputFile) {
    cerr << "Error opening file for writing: " << inputName << endl;
    return;
  }

  // Write header
  outputFile << "StudentNumber,FirstName,LastName,ProgrammingAssignmentGrade,"
                "TestGrade,FinalExamGrade\n";

  // Write updated student data
  for (int i = 0; i < studentCount; i++) {
    outputFile << stud[i].studNumber << "," << stud[i].firstName << ","
               << stud[i].lastName << ",";

    // Assuming one programming assignment and one test grade per student
    outputFile << stud[i].programGrade[0] << "," << stud[i].testGrade[0] << ","
               << stud[i].finalExamGrade << "\n";
  }

  outputFile.close();
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Function to calculate the final grade of students
inline void commands::calculateFinalGrade() {
  for (int i = 0; i < studentCount; i++) {
    // Calculate average program grade
    float sumProgram = 0.0;
    for (int x = 0; x < programCount; x++) {
      sumProgram += stud[i].programGrade[x];
    }
    stud[i].avgProgramGrade =
        (programCount > 0) ? sumProgram / programCount : 0.0;

    // Calculate average test grade
    float sumTest = 0.0;
    for (int x = 0; x < testCount; x++) {
      sumTest += stud[i].testGrade[x];
    }
    stud[i].avgTestGrade = (testCount > 0) ? sumTest / testCount : 0.0;

    // Calculate final grade based on weights
    stud[i].finalGrade = (stud[i].avgProgramGrade * programWeight +
                          stud[i].avgTestGrade * testWeight +
                          stud[i].finalExamGrade * finalWeight) /
                         100.0;
  }
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Function to remove newline characters from a string
void removeNewline(string &str) {
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

inline void commands::outputGrades() {
  outputName2 = "Grades.csv";
  ofstream outputFile(outputName2);

  // Write header line
  outputFile
      << "StudentID,Student,Program Grade,Test Grade,Final Exam,Class Grade\n";

  for (int i = 0; i < studentCount; i++) {
    // Remove newline characters from names
    removeNewline(stud[i].firstName);
    removeNewline(stud[i].lastName);

    // Write student data
    outputFile << stud[i].studNumber << "," << stud[i].firstName << " "
               << stud[i].lastName << "," << stud[i].avgProgramGrade << ","
               << stud[i].avgTestGrade << "," << stud[i].finalExamGrade << ","
               << stud[i].finalGrade << "\n";
  }
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
inline void commands::save() {
    outputName2 = "Grades.csv";
    ofstream outputFile(outputName2);

    if (!outputFile) {
        cerr << "Error opening file for writing: " << outputName2 << endl;
        return;
    }

    // Write CSV header
    outputFile << "StudentNumber,FirstName,LastName,";
    for (int i = 1; i <= programCount; i++) {
        outputFile << "ProgramGrade" << i << ",";
    }
    for (int i = 1; i <= testCount; i++) {
        outputFile << "TestGrade" << i << ",";
    }
    outputFile << "FinalExamGrade,FinalGrade\n";

    // Write student data in CSV format
    for (int i = 0; i < studentCount; i++) {
        outputFile << stud[i].studNumber << ","
                   << stud[i].firstName << ","
                   << stud[i].lastName << ",";
        for (int x = 0; x < programCount; x++) {
            outputFile << stud[i].programGrade[x] << ",";
        }
        for (int x = 0; x < testCount; x++) {
            outputFile << stud[i].testGrade[x] << ",";
        }
        outputFile << stud[i].finalExamGrade << ","
                   << stud[i].finalGrade << "\n";
    }
}
