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

struct Point {
  double x, y;
  double r;
  int i;
  // i is the number of line
};

int main(int argc, char** argv) {
  std::ifstream infile("radius.txt");
  std::ofstream ofs("assign100.txt");

  // Get length and height
  double length = 500;
  double height;
  
  // Should be input arguments
  // This should be the length and width of the column
  std::vector<double> radius;
  
  std::string line;

  if (infile.is_open()) {
    while (std::getline(infile, line)) {
      if (line != "") {
        std::istringstream istream(line);
        double r;
        istream >> r;
        radius.emplace_back(r);
      
      }
    }
  }
  infile.close();

  // Shuffles the vector of radius randomly
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(radius.begin(), radius.end(), g);

  // Maximum radius
  double max_radius = *(std::max_element(radius.begin(), radius.end()));

  // Vector of points
  std::vector<Point> points;

  double x = 0.;
  double y = max_radius;
  int i = 0;

  for (const auto& rad : radius) {
    // Initial x value
    x += rad;
    // Individual points
    Point p;
    p.r = rad;
    p.x = x;
    p.y = y;
    p.i = i;
    points.emplace_back(p);
    
    // Next start of x position
    x += rad;

    // Set new y, when the length is reached
    if (x >= length) {
      y += 2 * max_radius;
     //Make alternate lines more compact;
     if(i%2==0)
     x = 0.5*max_radius;
     else
     x = 0.;
     i=i+1;
    }
  }

  
  if (ofs.is_open()) {
    ofs<<std::setprecision(5)<<radius.size()<<"\n";
    for (auto point : points)
      ofs << std::setprecision(5)<< point.r << "\t" << std::setprecision(5)
          << point.x << "\t" << std::setprecision(5) << point.y << "\n";
    ofs.close();
  }


  // Write the output to file
  auto outfile1 = fopen("DEM.ps", "w");
  fprintf(outfile1, "%%!PS-Adobe-3.0 EPSF-3.0 \n");
  fprintf(outfile1, "%%%BoundingBox: %f %f %f %f \n", 0., 0., length+max_radius, y+max_radius);
  fprintf(outfile1, "%%%Creator: Krishna Kumar \n");
  fprintf(outfile1, "%%%Title: DEM Grains\n");
  fprintf(outfile1, "0.1 setlinewidth 0.0 setgray \n");
  for (auto point : points)
    fprintf(outfile1,
            "newpath %le %le %le 0.0 setlinewidth %.2f setgray 0 360 arc gsave "
            "fill grestore\n",
            point.x, point.y, point.r, 0.5);
  fclose(outfile1);

}
