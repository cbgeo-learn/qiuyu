#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

struct Point {
  double x,y,r;
};

int main(int argc, char** argv) {
  const double a = 0.8; //Aspect ratio I want;
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
  std::string line;
  double ignore;
  double max_x = 0.;
  double max_r = 0.;
  
   std::vector<Point> points;
  if (infile.is_open()) {
    while (std::getline(infile, line))
      if(!line.empty()){
        std::istringstream istream(line);
        Point p;
        istream>>ignore;
        istream>>p.r>>p.x>>p.y;
        istream>>ignore;
         if(p.x>max_x)max_x=p.x;
         if(p.r>max_r)max_r=p.r;
        points.emplace_back(p);
        
      }
    }
  
  infile.close();
 
  if (ofs.is_open()) {
          ofs <<std::setprecision(5)<<"MaxRadius:"<<1000*max_r<< "\t"\
          << std::setprecision(5)<<"MaxHeight:"<<1000*a*max_x<< "\t"\
          << std::setprecision(5)<<"MaxLength:"<<1000*max_x<<"\n";
        
       for (auto point : points)
          if(point.y<=a*max_x)
      ofs << std::setprecision(5)<< 1000*point.r << "\t" << std::setprecision(5)
          << 1000*point.x << "\t" << std::setprecision(5) << 1000*point.y << "\n";
    ofs.close();
  }

  
