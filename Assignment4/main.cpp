#include<iostream>
#include<fstream>
#include<string>
#include "commands.h"
using namespace std;

int main() {
    commands cmd;
    cmd.readGradesDat(); // Read data from Grades.dat

    // Loop that continues until user quits. 
    while (cmd.userAnswer != 'Q') {
        cout <<  "------------------------------------------------------------------------------------------\n";
        cout << "Instructions:\n";
        cout << "Enter 'S' to Set up for new semester.\n";
        cout << "Enter 'A' to Add a student.\n";
        cout << "Enter 'P' to Record programming assignment grade.\n";
        cout << "Enter 'T' to Record test grade.\n";
        cout << "Enter 'F' to Record Final exam grade.\n";
        cout << "Enter 'C' to Change a grade for a student.\n";
        cout << "Enter 'O' to Output the grade data.\n";
        cout << "Enter 'Q' to Quit. Save data and terminate the program.\n";
      cout << "------------------------------------------------------------------------------------------\n";
      cout << "Enter your command : ";
      cin >> cmd.userAnswer;
      cmd.userAnswer = toupper(cmd.userAnswer);

      switch (cmd.userAnswer) {
          case 'S':
              cmd.setUp();
            cmd.save();

              break;

          case 'A':
              cmd.addStudent();
            cmd.save();

              break;

          case 'P':
              cmd.recordProgramGrade();
              cmd.calculateFinalGrade();  // Recalculate final grades after recording
            cmd.save();

              break;

          case 'T':
              cmd.recordTestGrade();
              cmd.calculateFinalGrade();  // Recalculate final grades after recording
            cmd.save();

              break;

          case 'F':
              cmd.recordFinalGrade();
              cmd.calculateFinalGrade();  // Recalculate final grades after recording
            cmd.save();

              break;

          case 'C':
              cmd.changeGrade();
              cmd.calculateFinalGrade();  // Recalculate final grades after changes
            cmd.save();

              break;

          case 'O':
              cout << "O entered\n";
              cmd.calculateFinalGrade();
              cmd.outputGrades();
            cmd.save();
              break;

          case 'Q':
              cout << "Q entered\n";
              cmd.save();
              break;

          default:
              cout << "Invalid Response\n";
      }
      }

      return 0;  // End of main function
      }
