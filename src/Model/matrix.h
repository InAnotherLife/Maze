#ifndef SRC_MODEL_MATRIX_H_
#define SRC_MODEL_MATRIX_H_

#include <iostream>

namespace my {

class Matrix {
 public:
  Matrix(int rows, int columns);
  double &operator()(int i, int j);
  int get_rows();
  int get_columns();
  ~Matrix();

 private:
  int rows_;
  int columns_;
  double **matrix_;
};

}  // namespace my

#endif  //  SRC_MODEL_MATRIX_H_
