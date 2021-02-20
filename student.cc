#include <iostream>
#include "student.h"

Student::Student(){
  std::cout<<"Default constructor"<<std::endl;

}
Student::Student(std::string name, std::string desc)
{
  SetName(name);//the same as m_Name=name;
  m_desc=desc;//the same as SetDesc(desc);
  std::cout<<"Parameterized constructor(string,string)"<<std::endl;
  }
/*Also can be written as：
Student::Student(std::string name, std::string desc):m_Name(name),m_desc(desc){}
To initialize the list of arguments

*/

Student::Student(int age)
{
  SetAge(age);
  std::cout<<"Parameterized constructor(int)"<<std::endl;
}

void Student::ShowInfo(){
  std::cout<<m_desc<<m_Name<<m_age<<std::endl;
}
Student::~Student(){
  std::cout<<m_Name<<"is released"<<std::endl;
}

//Destructor: special member function called when the obejct expires and deleting objects; not paramterized


int main()
{
  Student stu1;
  Student stu2("Jack","Dandy");
  Student stu3(23);
  Student stu4=50;//equal stu4(50);used when the constructor has only one argument;
  stu2.ShowInfo();

  /*All above takes up stack memory, which is precious and fast at reading data. Heap memory is like the warehouse in Ikea while stack is like the display area.*/
  
  Student* stu5=new Student("Rachel","Sensitive");
  //Allocate as soon as initializing a constructor
  stu5->SetAge(30);
  stu5->ShowInfo();
  //Rachel wasn't released but all other constructors stored in stack were released;

  delete stu5;  //once the object ends, delete it asap.

}


