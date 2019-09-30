#include <cstdlib>
#include <iostream>
#include <string>
#include<cmath>

class Shape {
  public:
  Shape(const std::string& name) : name_{name} {}
  const std::string& name() { return name_;}

    virtual double area() =0;
    

  protected:
    std::string name_;
    double area_;

};

class Circle : public Shape {
  public:
    Circle(const std::string& name,double radius) : Shape(name) {}
  
    double area() override{
    std::cin>>radius_;
    return M_PI * std::pow(radius_,2);
    }

  private:
     double radius_;
};

class Triangle : public Shape {
  public:
     Triangle(const std::string& name,double width, double height) : Shape(name) {}

   double area() override{
    std::cin>>width_>>height_;
    return 0.5*width_*height_;
    }

  private:
     double width_;
     double height_;
};

class Rectangle : public Shape {
 public:
     Rectangle(const std::string& name,double width, double height) : Shape(name) {}

   double area() override{
    std::cin>>width_>>height_;
    return width_*height_;
    }

  private:
     double width_;
     double height_;
};

class  Ellipse : public Shape {
   public:
   Ellipse(const std::string& name,double axisa,double axisb) : Shape(name) {}
  
    double area() override{
    std::cin>> axisa_>>axisb_;
    return M_PI*axisa_*axisb_;
    }

  private:
     double axisa_;
     double axisb_;
};

int main() {

  Ellipse ee = Ellipse("Ellipse",5.0,6.0);
  Rectangle rr = Rectangle("Rectangle",5.0,6.0);
  Triangle tt = Triangle("Triangle",5.0,6.0);
  Circle cc = Circle("Circle",5.0);
  std::cout << "EllipseArea: " << ee.area() << std::endl;
  std::cout << "RectangleArea: " << rr.area() << std::endl;
  std::cout << "TriangleArea: " << tt.area() << std::endl;
  std::cout << "CircleArea: " << cc.area() << std::endl;
}
