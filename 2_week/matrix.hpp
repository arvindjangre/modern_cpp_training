#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <vector>
class Matrix {
private:
  const int rows;
  const int cols;

public:
  std::vector<std::vector<int>> mat;

  Matrix(int rows = 0, int cols = 0): rows{rows}, cols{cols}
  {
  }

  void fillValues();
  void printMatrix();

  Matrix operator+(Matrix &m2);
  Matrix operator*(Matrix &m2);
  friend std::ostream& operator<<(std::ostream&out, const Matrix& m);
};

#endif