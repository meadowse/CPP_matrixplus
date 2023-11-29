#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

#define EXP 1e-6

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void createMatrix();
  void copyMatrix(const S21Matrix& other);
  void cleanMatrix();

  S21Matrix CalcComplementsMinor(int i_rows, int j_cols);
  double RecursDeterminant(int n);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double& num) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num);
  double& operator()(int row, int cols);

  void setRows(int rows);
  void setCols(int cols);

  int getRows() const;
  int getCols() const;

  // void fillMatrix(const S21Matrix& other);
  // void printMatrix();
};

//     1 2 3       1 2 3
// A = 4 5 6   B = 4 5 6
//     7 8 9       7 8 9
#endif  // S21_MATRIX_OOP_H
