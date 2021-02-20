#include <iostream>

class Student
{
public:
  //Contructor has the same overloading rule as general functions
  Student();
  Student(std::string, std::string);//Parameterized constructor
  Student(int);//Parameterized constructor
  ~Student();

  void ShowInfo();
  std::string GetName(){return m_Name;}
  void SetName(std::string val){m_Name=val;}
  std::string GetDesc(){return m_desc;}
  void SetDesc(std::string val){m_desc=val;}
  int GetAge(){return m_age;}
  void SetAge(int val){m_age=(m_age<0?0:val);}

private:
  std::string m_Name,m_desc;
  int m_age=0;
  
};
