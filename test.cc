#include <cstdlib>
#include <iostream>

class Matrix {
public:
  Matrix(int rows, int cols);
  void data();
  void printMatrix();
  void val(int m, int n, double k);
  double val(int i, int j) const;
  Matrix operator +(Matrix b);

public:
  int rows_;
  int cols_;
  double** data_;
};

Matrix::Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    data_[i] = new double[cols_];
  }
}

void Matrix::data() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j)
      std::cin >> data_[i][j];
  }
}


void Matrix::printMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j)
      std::cout << data_[i][j] << " ";
    std::cout << '\n';
  }
}

double Matrix::val(int a, int b) const {
  return data_[a][b];
}

void Matrix:: val(int m, int n, double k){
data_[m][n]=k;
}

Matrix Matrix::operator +(Matrix b){
  Matrix c = Matrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      double x = data_[i][j]+b.val(i, j);
      c.val(i, j, x);
    }
  }
  return c;
}
 

int main() {
  Matrix a = Matrix(2, 2);
  a.data();
  a.printMatrix();
  Matrix b = Matrix(2, 2);
  b.data();
  b.printMatrix();

  auto c = a+b;
  c.printMatrix();

//  double **c=new double*[5];
// for (int i = 0; i < 5; ++i) {
//    for (int j = 0; j < 3; ++j)
//      c[i][j] = a.data[i][j] + b.data[i][j];
//  }
}
