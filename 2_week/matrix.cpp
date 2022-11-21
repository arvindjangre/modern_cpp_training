#include "matrix.hpp"

void Matrix::fillValues() {
  int temp;

  for (int i = 0; i < rows; i++) {
    std::vector<int> r;
    for (int j = 0; j < cols; j++) {
      std::cin >> temp;
      r.push_back(temp);
    }
    mat.push_back(r);
  }
}

Matrix Matrix::operator+(Matrix &m2) {
  if (rows != m2.rows || cols != m2.cols) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix Result(rows, cols);

  for (int i = 0; i < rows; i++) {
    std::vector<int> r;
    for (int j = 0; j < cols; j++) {
      r.push_back(mat[i][j] + m2.mat[i][j]);
    }
    Result.mat.push_back(r);
  }
  return Result;
}

Matrix Matrix::operator*(Matrix &m2) {
  if (cols != m2.rows) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix Result(rows, cols);
  Result.mat.resize(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Result.mat[i][j] = 0;
      for(int k = 0; k < cols; k++) {
        Result.mat[i][j] +=  mat[i][k] * m2.mat[k][j];
      }
    }
  }
  return Result;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
  if (out) {

    for (int i = 0; i < m.rows; i++) {
      for (int j = 0; j < m.cols; j++) {
        out << m.mat[i][j] << " ";
      }
      out << std::endl;
    }
  }
  return out;
}
