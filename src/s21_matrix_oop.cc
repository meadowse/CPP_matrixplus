#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() { cleanMatrix(); }

// --------------------------------------------------------------------------------------------

// void S21Matrix::fillMatrix(const S21Matrix& other) {
//   int s = 0;
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       matrix_[i][j] = s * s;
//       s++;
//     }
//   }
//   s = 0;
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       other.matrix_[i][j] = s + s;
//       s++;
//     }
//   }
// }

// void S21Matrix::printMatrix() {
//     for(int i = 0; i < rows_; i++) {
//         for (int j = 0; j < cols_; j++) {
//             std::cout << " matrix[" << i << "][" << j << "] = " <<
//             matrix_[i][j] << "\n";
//         }
//         std::cout << "\n";
//     }

// for(int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//         std::cout << "matrix[" << i << "][" << j << "] = " <<
//         matrix_[i][j] << "\n";
//     }
//     std::cout << "\n";
// }
// }

// --------------------------------------------------------------------------------------------

void S21Matrix::createMatrix() {
  matrix_ = new double*[rows_]();
  for (auto i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::copyMatrix(const S21Matrix& other) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::cleanMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = cols_ = 0;
  }
}

// --------------------------------------------------------------------------------------------

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EXP) {
        result = false;
        break;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: Rows first matrix not equal columns second matrix");
  }
  S21Matrix array(rows_, other.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < other.cols_; j++) {
      array.matrix_[i][j] = 0;
      for (auto x = 0; x < cols_; x++) {
        array.matrix_[i][j] += matrix_[i][x] * other.matrix_[x][j];
      }
    }
  }
  setCols(other.cols_);
  copyMatrix(array);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix array(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      array.matrix_[j][i] = matrix_[i][j];
    }
  }
  return array;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_)
    throw std::invalid_argument("Error: The matrix is not square.");
  S21Matrix result(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      double determinant = 0;
      S21Matrix new_minor = CalcComplementsMinor(i, j);
      determinant = new_minor.Determinant();
      determinant = determinant * pow(-1, i + j);
      result.matrix_[i][j] = determinant;
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplementsMinor(int i_rows, int j_cols) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (auto i = 0, mini_i = 0; i < rows_; i++) {
    if (i == i_rows) continue;
    for (auto j = 0, mini_j = 0; j < cols_; j++) {
      if (j == j_cols) continue;
      result.matrix_[mini_i][mini_j] = matrix_[i][j];
      mini_j++;
    }
    mini_i++;
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Error: It is impossible to calculate the determinant!");
  }
  double result;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    result = RecursDeterminant(rows_);
  }
  return result;
}

double S21Matrix::RecursDeterminant(int n) {
  double det = 0.0;
  if (n == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    S21Matrix SubMatrix(rows_, cols_);
    for (auto c = 0; c < n; c++) {
      int SubMatrix_i = 0;
      for (auto i = 1; i < n; i++) {
        int SubMatrix_j = 0;
        for (auto j = 0; j < n; j++) {
          if (j != c) {
            SubMatrix.matrix_[SubMatrix_i][SubMatrix_j] = matrix_[i][j];
            SubMatrix_j++;
          }
        }
        SubMatrix_i++;
      }
      det += pow(-1, c) * matrix_[0][c] * SubMatrix.RecursDeterminant(n - 1);
    }
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determ = Determinant();
  if (fabs(determ) < EXP) {
    throw std::range_error("Error: Determinant is 0");
  }
  S21Matrix complements_matrix(CalcComplements());
  S21Matrix transpose_matrix(complements_matrix.Transpose());
  return transpose_matrix * (1.0 / determ);
}

// --------------------------------------------------------------------------------------------

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix array(*this);
  array.SumMatrix(other);
  return array;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix array(*this);
  array.SubMatrix(other);
  return array;
}

S21Matrix S21Matrix::operator*(const double& num) const {
  S21Matrix array(*this);
  array.MulNumber(num);
  return array;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix array(*this);
  array.MulMatrix(other);
  return array;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

// S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//   if (*this == &other)
//     return *this;
//     cleanMatrix();
//     rows_ = other.rows_;
//     cols_ = other.cols_;
//     createMatrix();
//     copyMatrix(other);
//   return *this;
// }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (*this == other) {
    return *this;
  }
  cleanMatrix();
  rows_ = other.rows_, cols_ = other.cols_;
  createMatrix();
  copyMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  // std::cout << row << "&&" << cols;
  return matrix_[row][col];
}

// ---------------------------------------------------------------------------------------------------------------------------------

void S21Matrix::setRows(int rows) {
  S21Matrix tmp_this(*this);
  cleanMatrix();
  rows_ = rows;
  cols_ = tmp_this.getCols();
  createMatrix();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = (i < tmp_this.getRows()) ? tmp_this.matrix_[i][j] : 0;
    }
  }
}

void S21Matrix::setCols(int cols) {
  S21Matrix tmp_this(*this);
  cleanMatrix();
  rows_ = tmp_this.getCols();
  cols_ = cols;
  createMatrix();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = (j < tmp_this.getCols()) ? tmp_this.matrix_[i][j] : 0;
    }
  }
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

// int main() {
//   S21Matrix array1(2, 2);
//   array1(1, 1) = 1.2;
//   S21Matrix array2(array1);
//   // S21Matrix matrix_a(3, 6);
//   //   matrix_a(0, 0) = 2;
//   //   matrix_a(0, 1) = 5;
//   //   matrix_a(0, 2) = 7;
//   //   matrix_a(1, 0) = 10;
//   //   matrix_a(1, 1) = 3;
//   //   matrix_a(1, 2) = 4;
//   //   matrix_a(2, 0) = 5;
//   //   matrix_a(2, 1) = -2;
//   //   matrix_a(2, 2) = -3;
//   //   matrix_a.printMatrix();
//   //   S21Matrix matrix_b = matrix_a.InverseMatrix();
//   //   matrix_b.printMatrix();

//   //   S21Matrix matrix_c(3, 3);
//   //   matrix_c(0, 0) = 1;
//   //   matrix_c(0, 1) = -1;
//   //   matrix_c(0, 2) = 1;
//   //   matrix_c(1, 0) = -38;
//   //   matrix_c(1, 1) = 41;
//   //   matrix_c(1, 2) = -34;
//   //   matrix_c(2, 0) = 27;
//   //   matrix_c(2, 1) = -29;
//   //   matrix_c(2, 2) = 24;
// }