#include <iostream>
#include <string>
#include<cmath>
#include <cstdlib>

#define PI acos(-1)


class Shape {
  public:
  Shape(std::string name) : name_{name} {}
  std::string name() { return name_;}

    virtual double area() {
    std::cin>>width_;
    std::cin>>height_;
    area_= width_*height_;
    return area_;
    }

  protected:
    std::string name_;
    double width_;
    double height_;
    double radius_;
    double area_;

};

class Circle : public Shape {
  public:
    Circle(std::string name) : Shape(name) {}
  
    double area() {
    std::cin>>radius_;
    area_= PI*radius_*radius_;
    return area_;
    }

    void print() { 
      std::cout << name_ << std::endl;
      std::cout << "Area: " << area_ << std::endl; }
  private:
     double radius_;
};

class Triangle : public Shape {
  public:
     Triangle(std::string name) : Shape(name) {}

    void print() { 
      std::cout << name_ << std::endl;
      std::cout << "Area: " << 0.5*area_ << std::endl; }
  private:
     double width_;
     double height_;
};

class Rectangle : public Shape {
  public:
     Rectangle(std::string name) : Shape(name) {}

    void print() { 
      std::cout << name_ << std::endl;
      std::cout << "Area: " << area_ << std::endl; }
  private:
     double width_;
     double height_;
};

class  Ellipse : public Shape {
  public:
     Ellipse(std::string name) : Shape(name) {}

    void print() { 
      std::cout << name_ << std::endl;
      std::cout << "Area: " << PI*area_ << std::endl; }
  private:
     double width_;
     double height_;
};

int main() {
  Circle cc = Circle("Circle");
  Triangle tt = Triangle("Triangle");
  Rectangle rr = Rectangle("Rectangle");
  Ellipse ee=Ellipse("Ellipse");
  cc.area();
  cc.print();
  tt.area();
  tt.print();
  rr.area();
  rr.print();
  ee.area();
  ee.print();


}
