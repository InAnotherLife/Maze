#include "matrix.h"

namespace my {

Matrix::Matrix(int rows, int cols) : rows_(rows), columns_(cols) {
  if (rows_ < 0 || columns_ < 0)
    throw std::out_of_range("Rows or Columns cannot be less 0");
  if (rows_ == 0 || columns_ == 0) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) matrix_[i] = new double[columns_]{0};
  }
}

Matrix::~Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) {
        delete[] matrix_[i];
        matrix_[i] = nullptr;
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  columns_ = 0;
}

double &Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0)
    throw std::out_of_range("Wrong value of index! Indexes cannot be less 0");
  if (i > (rows_ - 1) || j > (columns_ - 1))
    throw std::out_of_range(
        "Wrong value of index! Value exceeds the size of the matrix.");
  return this->matrix_[i][j];
}

int Matrix::get_rows() { return rows_; }

int Matrix::get_columns() { return columns_; }

}  // namespace my
