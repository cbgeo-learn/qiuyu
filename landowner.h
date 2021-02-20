#include <iostream>
#include <vector>

class Landowner
/**/
{
private:
  std::string m_Name,m_Sex;
  int m_Gold;
  long m_Exp;
  std::vector<int> packCards;//Default deck of cards(1-54);
  std::vector<int> surplusCards;//Surplus of cards
  std::vector<int> currCards;//Current player's hand
  bool isContains(int); //If the surplus contains the card 
  void deleteCard(std::vector<int>&,int);
  std::string getColor(int);
  std::string getValue(int);
public:
  //Contructor has the same overloading rule as general functions
  Landowner();
  Landowner(std::string);
  Landowner(std::string,std::string,int,long);//Parameterized constructor
  // Landowner(int);//Parameterized constructor
  ~Landowner();

  std::string GetName(){return m_Name;}
  void SetName(std::string val){m_Name=val;}
  std::string GetSex(){return m_Sex;}
  void SetSex(std::string val){m_Sex=val;}
  int GetGold(){return m_Gold;}
  void SetGold(int val){m_Gold=(m_Gold<0?0:val);}
  long GetExp(){return m_Exp;}
  void SetExp(long val){m_Exp=val;}

  void ShowInfo();
  void TouchCard(int);
  void InitCards();//Initialize packCards and surplusCards and currCards
  void ShowCards(const std::vector<int>&);
};
