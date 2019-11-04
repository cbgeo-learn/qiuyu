#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#define a 0.8
struct Point {
  double x,y,r;
  //std::vector<double> y;
};

int main(int argc, char** argv) {
  std::string inputfile, outputfile;
  if (argc == 3) {
    inputfile = argv[1];
    outputfile = argv[2];
  } else {
    std::cerr << "Incorret number of arguments." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::ifstream infile(inputfile);
  std::ofstream ofs(outputfile);
  std::vector<Point> points;
  std::string line;
 
  std::vector<std::string>vec;
  if (infile.is_open()) {
    while (std::getline(infile, line))
      if(line!=""){
      
        std::string linesub = line.substr (0,50);
        //   std::istringstream istream(line);
        vec.emplace_back(linesub);
      }
    }
  
  infile.close();
 
   double max_x = 0.;
  for (auto it =vec.begin();it!=vec.end();it++)
  {
    std::istringstream pt(*it);
    std::string s;
    int pam = 0;
    Point p;
      
     while(pt>>s)
    {  
      if(pam==1)
        p.r=std::stod(s.c_str());
      if(pam==2)
        p.x=std::stod(s.c_str());
        if(p.x>max_x)max_x=p.x;
       if(pam==3)
        p.y=std::stod(s.c_str());
       pam++;
         }
      points.emplace_back(p);

  }

  
  if (ofs.is_open()) {
 //  ofs<<std::setprecision(5)<<radius.size()<<"\n";
    for (auto point : points)
      if(point.y<=a*max_x)
      ofs << std::setprecision(5)<< point.r << "\t" << std::setprecision(5)
          << point.x << "\t" << std::setprecision(5) << point.y << "\n";
    ofs.close();
  }
  }
