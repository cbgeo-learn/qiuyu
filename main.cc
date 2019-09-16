#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  const double radius_a = 2;
  std::vector<double> radii;
  std::srand((unsigned)time(NULL));

  int nparticles; 
  if (argc == 2)
    nparticles = atoi(argv[1]);

  for (int i = 0; i < nparticles; ++i)
    radii.push_back(radius_a + 2.0 * std::rand() / double(RAND_MAX));
 
  for (auto radius : radii)
    std::cout << radius << std::endl;
}
