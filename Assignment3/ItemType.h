/*
Assignment 3 ItemType.h
Date: 9/7/2021
Student 1: Quang Nguyen si4359
Student 2: Beatriz Santos bw4673 
Student 3: Anthony Schultz vt7482
*/
// The following declarations and definitions go into file 
// ItemType.h. 
ItemType::ItemType()
{ 
  value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const 
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else return EQUAL;
}

void ItemType::Initialize(int number) 
{
  value = number;
}

void ItemType::Print(std::ostream& out) const 
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
  out << value;
}
