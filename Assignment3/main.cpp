/*
Assignment 3 main.cpp
Date: 9/7/2021
Student 1: Quang Nguyen si4359
Student 2: Beatriz Santos bw4673 
Student 3: Anthony Schultz vt7482
*/ 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "ItemType.cpp"
#include "ItemType.h"
using namespace std;

int main() {
  vector <string> lineVec;
  vector <ItemType> userList;
  string inputName = "listData.txt";
  string outputName = "outputFile.txt";
  string testName;
  string line;  
  string temp;  
  ItemType element;
  int commandCount = 1;
  bool found;


  cout << "Enter the name of the input file then press return \n";
  cin >> inputName;
  cout << "Enter the name of the output file then press return \n";
  cin >> outputName;
  cout << "Enter the name of the test run then press return \n";
  cin >> testName;

  // Sets input file and output file
  ifstream inputFile(inputName);
  ofstream outputFile(outputName);
  outputFile << testName << "\n"; 

  // Adds each line to line vector
  while(getline(inputFile,line))
  {
    lineVec.push_back(line);
  }

  for (int x = 0; x < sizeof(lineVec); x++) 
  {
  // ------------------------------------------------------
  // Function to get length
  if (lineVec[x].find("GetLength") != std::string::npos)
    {
      outputFile << "Length is " << userList.size() << "\n";
      cout << "Command number " << commandCount << " completed.\n";
      commandCount++;          
      }
  // ------------------------------------------------------
  // ------------------------------------------------------
  // Function to insert item in unsorted list
  else if (lineVec[x].find("PutItem") != std::string::npos)
    {
      temp = lineVec[x];
      size_t i = 0;
      for ( ; i < temp.length(); i++ )
      { 
        if (isdigit(temp[i])) break; 
      }
      temp = temp.substr(i, temp.length() - i );
      element.Initialize(atoi(temp.c_str()));
      if (userList.size() > MAX_ITEMS)
      {
        outputFile << "List is full, element cannot be added. \n";
        cout << "Command number " << commandCount << " completed.\n";
      }
      else
      {
        userList.push_back(element);
        element.Print(outputFile);
        outputFile << " is in list. \n";
        cout << "Command number " << commandCount << " completed.\n";
        commandCount++;
      }
    }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to print unsorted list
  else if (lineVec[x].find("PrintList") != std::string::npos)
    {
      for (int i = userList.size()-1; i >= 0; i--) 
      {
        userList[i].Print(outputFile);
      }
        outputFile << "\n";
      cout << "Command number " << commandCount << " completed.\n";
      commandCount++;
    }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to get element from unsorted list
  else if (lineVec[x].find("GetItem") != std::string::npos)
    {
      temp = lineVec[x];
      size_t i = 0;
      for ( ; i < temp.length(); i++ )
      { 
        if (isdigit(temp[i])) break; 
      }
      temp = temp.substr(i, temp.length() - i );
      element.Initialize(atoi(temp.c_str()));
      
      for (int i = 0; i < userList.size(); i++)
      {
        found=false;
        if (element.ComparedTo(userList.at(i)) == EQUAL)
        {
          element.Print(outputFile);
          outputFile << " found in list.\n";
          cout << "Command number " << commandCount << " completed.\n";
          found = true; 
          break;
        }
      }
      if (!found)
      {
        element.Print(outputFile);
        outputFile << " not found in list.\n";
      }
      commandCount++;  
    }

  // ------------------------------------------------------
  // NOT SURE WHAT TO DO
  else if (lineVec[x].find("IsFull") != std::string::npos)
    {
      if (userList.size() == MAX_ITEMS)
      {
        outputFile << "List is full. \n";
        cout << "Command number " << commandCount << " completed.\n";
      }      
      else
      {
      outputFile << "List is not full. \n";
      cout << "Command number " << commandCount << " completed.\n";
      }
      commandCount++;  
    }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to delete element from list.
  else if (lineVec[x].find("DeleteItem") != std::string::npos)
    {
      temp = lineVec[x];
      size_t i = 0;
      for ( ; i < temp.length(); i++ )
      { 
        if (isdigit(temp[i])) break; 
      }
      temp = temp.substr(i, temp.length() - i );
      element.Initialize(atoi(temp.c_str()));
      
      for (int i = 0; i < userList.size(); i++)
      {
        found=false;
        if (element.ComparedTo(userList.at(i)) == EQUAL)
        {
          userList.erase(userList.begin()+i);
          element.Print(outputFile);
          outputFile << " is deleted\n";
          found = true; 
          break;
        }
      }
      if (!found)
      {
        element.Print(outputFile);
        outputFile << " not found in list so cannot be deleted.\n";
      }
          
      cout << "Command number " << commandCount << " completed.\n";
      commandCount++;      
      }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to clear contents of list
  else if (lineVec[x].find("MakeEmpty") != std::string::npos)
    {
      userList.clear();
      cout << "Command number " << commandCount << " completed.\n";
      commandCount++;     
    }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to stop reading from file IE quit program
  else if (lineVec[x].find("Quit") != std::string::npos)
    {
      outputFile << "";
      inputFile.close();
      outputFile.close();
      cout << "Command number " << commandCount << " completed.\n";
      commandCount++;     
      break; 
      }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to get element from unsorted list
  else if (lineVec[x] == "")
  {
    cout << "";
  }
  // ------------------------------------------------------

  // ------------------------------------------------------
  // Function to get element from unsorted list
  else
  {
      outputFile << "";
      cout << lineVec[x] << " is not a valid command\n";
  }
  // ------------------------------------------------------
  }
  inputFile.close();
  outputFile.close();
  cout << "Tesing completed.";
}