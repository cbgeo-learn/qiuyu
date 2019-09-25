#include <cstdlib>
#include <iostream>

class Matrix {
public:
  Matrix(int rows, int cols);
  void data();
  void printMatrix();

private:
  int rows_;
  int cols_;
};

Matrix::Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  double **data;
  data = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    data[i] = new double[cols_];
  }
}

void Matrix::data() {
  double **data;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j)
      std::cin >> data[i][j];
  }


void Matrix::printMatrix() {
  double **data;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j)
      std::cout << data[i][j] << " ";
    std::cout << '\n';
  }
}

int main() {
  Matrix a = Matrix(5, 3);
  a.data();
  a.printMatrix();
  Matrix b = Matrix(5, 3);
  b.data();
  b.printMatrix();
  double **c=new double*[5];
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 3; ++j)
      c[i][j] = a.data[i][j] + b.data[i][j];
  }
i}
