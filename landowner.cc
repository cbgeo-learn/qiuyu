#include <iostream>
#include "landowner.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Landowner::Landowner(){
  SetName("Default landowner");
  SetSex("Secret");
  SetExp(0);
  SetGold(1000);
  std::cout<<"Landowner()"<<std::endl;
}
Landowner::Landowner(std::string name):m_Name(name)
{
  SetSex("Secret");
  SetExp(0);
  SetGold(1000);
  std::cout<<"Landowner(Name)"<<std::endl;
  InitCards();
  ShowCards(packCards);
}

Landowner::Landowner(std::string name, std::string sex,int gold,long exp):m_Name(name),m_Sex(sex),m_Gold(gold),m_Exp(exp)
{
  std::cout<<"Landowner(Name,sex,gold,exp)"<<std::endl;
  InitCards();
  }

void Landowner::ShowInfo(){
  std::cout<<"Name: "<<m_Name<<std::endl;
  std::cout<<"Sex: "<<m_Sex<<std::endl;
  std::cout<<"Gold: "<<m_Gold<<std::endl;
  std::cout<<"Exp: "<<m_Exp<<std::endl;
}

void Landowner::InitCards()//Initialize packCards and surplusCards and currCards
{for(int i=0;i<54;i++){
    packCards.push_back(i+1);
    surplusCards.push_back(i+1);}
    //Or: surplusCards.push_back(packCards.at(i)); 
    currCards.clear();
}

void Landowner::ShowCards(const std::vector<int>& cards){
  /*Several ways to iterate through a vector*/
  for(const auto& card:cards) std::cout<<card<<": "<<getColor(card)<<"-"<<getValue(card)<<"\t";}
  //for(int i=0;i<cards.size();i++)std::cout<<cards.at(i)<<", ";
  //for(std::vector<int>::const_iterator iter=cards.begin();iter!=cards.end();iter++)std::cout<<*iter<<", ";
  //for(auto iter=cards.begin();iter!=cards.end();iter++)std::cout<<*iter<<", ";
  /*#include<iterator>#include<algorithm>*/
  //copy(cards.cbegin(),cards.cend(),std::ostream_iterator<int>(std::cout,","));}

void Landowner::TouchCard(int cardsCount)
  {//Randomly generate a card from the surplus of cards and remove it from the surplus
    srand(time(NULL));
    for(int i=0;i<cardsCount;i++){
      int randIndex=rand()%54;//random number between 0 and 53
      //Determine if the card is in the surplus
      if (isContains(packCards[randIndex])){
        currCards.push_back(packCards[randIndex]);
      //Remove it from the surplus
        deleteCard(surplusCards,packCards[randIndex]);}
      else{i--;}
    }
    std::cout<<"<Touch card> - current cards are: "<<std::endl;
    ShowCards(currCards);
    std::cout<<"\n"<<"Surplus cards are: "<<std::endl;
    ShowCards(surplusCards);
    std::cout<<"\n";
}

bool Landowner::isContains(int cardNum)
{
  std::vector<int>::iterator iter=find(surplusCards.begin(),surplusCards.end(),cardNum);
  // if(iter == surplusCards.end()){return false;}
  //return true;
  return iter!=surplusCards.end();

  /*General way:
    for int i=0;i<surplusCards.size();i++){
    if(surplusCards[i]==cardNum)return true;}
    return false;*/
}

void Landowner::deleteCard(std::vector<int>& cardsVec,int card){
  /*for(auto iter=cardsVec.begin();iter!=cardsVec.end();iter++)
    {if(*iter==card)iter=cardsVec.erase(iter);//return the pointer to the next element to the erased one
    else{++iter;}//++ should be ahead of iter
    }*/
  auto iter=find(cardsVec.begin(),cardsVec.end(),card);
  if(iter!=cardsVec.end()){cardsVec.erase(iter);}
}

std::string Landowner::getColor(int card){
  if(card==53)return "Black joker";
  if(card==54)return "Red joker";
  std::string colors[]={"Spade","Heart","Club","Diamond"};
  return colors[(card-1)/13];
}

std::string Landowner::getValue(int card){
  if(card==53)return "Black joker";
  if(card==54)return "Red joker";
  std::string values[]={"A","2","3","4","5","6","7","8","9","10",
  "J","Q","K"};
  return values[(card-1)%13];
}

Landowner::~Landowner(){
  std::cout<<m_Name<<"is released"<<std::endl;
}

int main()
{
  Landowner* ptr_landowner1=new Landowner();
  Landowner* ptr_landowner2=new Landowner("Expert");
  Landowner* ptr_landowner3=new Landowner("Rookie");

  ptr_landowner1->ShowInfo();
  ptr_landowner2->ShowInfo();
  ptr_landowner3->ShowInfo();

  ptr_landowner2->TouchCard(20);

  delete ptr_landowner1;
  delete ptr_landowner2;
  delete ptr_landowner3;
}


