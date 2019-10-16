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
};

int main(int argc, char** argv) {
  std::ifstream infile("radius.txt");
  std::ofstream ofs("assign100.txt");

  // Get length and height
  double length = 20;
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

  for (const auto& rad : radius) {
    // Initial x value
    x += rad;
    // Individual points
    Point p;
    p.r = rad;
    p.x = x;
    p.y = y;

    points.emplace_back(p);
    
    // Next start of x position
    x += rad;

    // Set new y, when the length is reached
    if (x >= length) {
      y += 2 * max_radius;
      x = 0.;
    }
  }

  
  if (ofs.is_open()) {
    for (auto point : points)
      ofs << std::setprecision(5) << point.r << "\t" << std::setprecision(5)
          << point.x << "\t" << std::setprecision(5) << point.y << "\n";
    ofs.close();
  }
}
