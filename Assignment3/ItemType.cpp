/*
Assignment 3 ItemType.cpp
Date: 9/7/2021
Student 1: Quang Nguyen si4359
Student 2: Beatriz Santos bw4673 
Student 3: Anthony Schultz vt7482
*/
// The following definitions go into file ItemType.cpp. 
#include <fstream>
#include <iostream>

const int MAX_ITEMS = 5;
enum RelationType  {LESS, GREATER, EQUAL};

class ItemType 
{ 
public:
  ItemType();
  RelationType ComparedTo(ItemType) const;
  void Print(std::ostream&) const;
  void Initialize(int number);
private:
  int value;
};

