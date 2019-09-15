
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  const double radius_a = 2;
  double radius;
  std::srand((unsigned)time(NULL));
  for (int i = 0; i < 100; ++i) {
    radius = radius_a + 2.0 * std::rand() / double(RAND_MAX);
    std::cout << radius << std::endl;
  }
}
