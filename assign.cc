#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {

  std::ifstream infile("radius.txt");
  std::ofstream ofs("assign100.txt");
  int rows = 100;
  int cols = 100;
  int number = rows * cols;
  double radius[number] = {0};
  double xpost[number] = {0};
  double ypost[number] = {0};
  std::string line;
  int i = 0;
  
    if (infile.is_open()) 
      while (std::getline(infile, line)) {
        if (line != "") {
          std::istringstream istream(line);
          istream >> radius[i];
          i = i + 1;
         if(i>number)
           break;
        }
      }
  infile.close();

  for (int i = 0; i < number; i = i + cols)
    for (int j = 1; j < cols; ++j)
      xpost[i + j] = xpost[j - 1] + radius[j] + radius[j - 1];

  for (int i = cols; i < number; i = i + cols)
    for (int j = 0; j < cols; ++j)
      ypost[i + j] =
          ypost[i + j - cols] + radius[i + j - cols] + 2 * radius[i + j];

  for (int i = 0; i < number; ++i)
    if (ofs.is_open()) {

      ofs << radius[i] << " " << xpost[i] << " " << ypost[i] << "\n";
    }
  ofs.close();

    }
