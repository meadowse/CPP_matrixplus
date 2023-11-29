#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

/*
    Информация о классе:
    Стандартный конструктор без входных параметров создает матрицу 3 на 3 в
   matrix также записывает обратную матрицу данной в i_matrix, также с матрицей
    алгебраических дополнений и записывает в alg_matrix.
    Конструктор с одним входным параметром status
      При status = 0 матрица из стандартного конструктора (matrix)
    обрезается с сохранением значений до размера 2 на 2
      При status = 1 matrix будет иметь размер 3 на 3 с нулевыми значениями
      При status = 2 matrix будет иметь размер 4 на 4 с другими значениями
      При status = 3 в matrix будет лежать матрица 3 на 3 но ее значения будут
    значениями квадрата матрицы (matrix) из стандартного конструктора
      При status = 4 в matrix будет лежать матрица 3 на 3 но ее значения будут
    значениями матрица (matrix) умноженной на 2 из стандартного конструктора
      При status = 5 в matrix будет лежать матрица 2 на 3 и будет записан ее
    трансонированный вариант в t_matrix
    Важно! Там где НЕ упомянуто что значения i_matrix, t_matrix и
    alg_matrix НАЙДЕНЫ их НЕ ИСПОЛЬЗОВАТЬ! Они будут иметь нулевые значения!
*/
class TestS21Matrix {
 public:
  TestS21Matrix() {
    matrix(0, 0) = 7, matrix(0, 1) = 8, matrix(0, 2) = 3;
    matrix(1, 0) = 5, matrix(1, 1) = 9, matrix(1, 2) = 1;
    matrix(2, 0) = 9, matrix(2, 1) = 4, matrix(2, 2) = 2;

    i_matrix(0, 0) = -0.150538, i_matrix(0, 1) = 0.0430108,
                i_matrix(0, 2) = 0.204301;
    i_matrix(1, 0) = 0.0107527, i_matrix(1, 1) = 0.139785,
                i_matrix(1, 2) = -0.0860215;
    i_matrix(2, 0) = 0.655914, i_matrix(2, 1) = -0.473118,
                i_matrix(2, 2) = -0.247312;

    alg_matrix(0, 0) = 14, alg_matrix(0, 1) = -1, alg_matrix(0, 2) = -61;
    alg_matrix(1, 0) = -4, alg_matrix(1, 1) = -13, alg_matrix(1, 2) = 44;
    alg_matrix(2, 0) = -19, alg_matrix(2, 1) = 8, alg_matrix(2, 2) = 23;
  }
  TestS21Matrix(int status) {
    if (status == 0) {
      matrix.setCols(2);
      matrix.setRows(2);
      matrix(0, 0) = 7, matrix(0, 1) = 8;
      matrix(1, 0) = 5, matrix(1, 1) = 9;
    }
    if (status == 1) {
    }
    if (status == 2) {
      matrix.setRows(4);
      matrix.setCols(4);
      matrix(0, 0) = 1.2, matrix(1, 0) = 10.2, matrix(2, 0) = 5.8,
                matrix(3, 0) = 2.6, matrix(0, 1) = 4.8, matrix(1, 1) = -6.7;
      matrix(2, 1) = 3.45, matrix(3, 1) = -8.9, matrix(0, 2) = -3.2;
      matrix(1, 2) = 1.9, matrix(2, 2) = -7.8, matrix(3, 2) = 2.2;
      matrix(0, 3) = 9.08, matrix(1, 3) = 9.1, matrix(2, 3) = 0.34,
                matrix(3, 3) = -1.5;
    }
    if (status == 3) {
      matrix(0, 0) = 116, matrix(0, 1) = 140, matrix(0, 2) = 35;
      matrix(1, 0) = 89, matrix(1, 1) = 125, matrix(1, 2) = 26;
      matrix(2, 0) = 101, matrix(2, 1) = 116, matrix(2, 2) = 35;
    }
    if (status == 4) {
      matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
      matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
      matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
    }
    if (status == 5) {
      matrix.setCols(3);
      matrix.setRows(2);
      matrix(0, 0) = 0, matrix(0, 1) = 1, matrix(0, 2) = 2;
      matrix(1, 0) = 3, matrix(1, 1) = 4, matrix(1, 2) = 5;

      t_matrix.setCols(2);
      t_matrix.setRows(3);
      t_matrix(0, 0) = 0, t_matrix(0, 1) = 3;
      t_matrix(1, 0) = 1, t_matrix(1, 1) = 4;
      t_matrix(2, 0) = 2, t_matrix(2, 1) = 5;
    }
  }
  S21Matrix matrix;
  S21Matrix t_matrix;
  S21Matrix i_matrix;
  S21Matrix alg_matrix;
};

TEST(DefaultConstructorTest, SingleTest) {
  S21Matrix array1;
  ASSERT_NEAR(0.0, array1(0, 0), EXP);
}

TEST(ConstructorWithIntegerParameters, CorrectInput) {
  S21Matrix array1(2, 2);
  ASSERT_NEAR(0.0, array1(0, 0), EXP);
  ASSERT_NEAR(0.0, array1(0, 1), EXP);
  ASSERT_NEAR(0.0, array1(1, 0), EXP);
  ASSERT_NEAR(0.0, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(CopyConstructor, SingleTest) {
  S21Matrix array1(2, 2);
  array1(1, 1) = 1.2;
  S21Matrix array2(array1);
  ASSERT_NEAR(0.0, array2(0, 0), EXP);
  ASSERT_NEAR(0.0, array2(0, 1), EXP);
  ASSERT_NEAR(0.0, array2(1, 0), EXP);
  ASSERT_NEAR(1.2, array2(1, 1), EXP);
  ASSERT_EQ(2, array2.getRows());
  ASSERT_EQ(2, array2.getCols());
}

TEST(MoveConstructor, SingleTest) {
  S21Matrix array1(2, 2);
  array1(1, 1) = 1.2;
  S21Matrix array2(std::move(array1));
  ASSERT_NEAR(0.0, array2(0, 0), EXP);
  ASSERT_NEAR(0.0, array2(0, 1), EXP);
  ASSERT_NEAR(0.0, array2(1, 0), EXP);
  ASSERT_NEAR(1.2, array2(1, 1), EXP);
  ASSERT_EQ(2, array2.getRows());
  ASSERT_EQ(2, array2.getCols());
  ASSERT_EQ(0, array1.getRows());
  ASSERT_EQ(0, array1.getCols());
}

TEST(EqMatrix, Equal) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  ASSERT_NEAR(1, array1.EqMatrix(array2), EXP);
}

TEST(SumMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  array1.SumMatrix(array2);
  ASSERT_NEAR(1.2, array1(0, 0), EXP);
  ASSERT_NEAR(0.0, array1(0, 1), EXP);
  ASSERT_NEAR(2.5, array1(1, 0), EXP);
  ASSERT_NEAR(0.0, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(SubMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  array1.SubMatrix(array2);
  ASSERT_NEAR(1.2, array1(0, 0), EXP);
  ASSERT_NEAR(0.0, array1(0, 1), EXP);
  ASSERT_NEAR(-2.5, array1(1, 0), EXP);
  ASSERT_NEAR(0.0, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(TransposeMatrix, SqrMatrix) {
  S21Matrix array1(2, 2);
  array1(0, 0) = 1;
  array1(0, 1) = 2;
  array1(1, 0) = 3;
  array1(1, 1) = 4;
  array1 = array1.Transpose();
  ASSERT_NEAR(1, array1(0, 0), EXP);
  ASSERT_NEAR(3, array1(0, 1), EXP);
  ASSERT_NEAR(2, array1(1, 0), EXP);
  ASSERT_NEAR(4, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(DeterminantMatrix, MatrixSqrOne) {
  S21Matrix array1(1, 1);
  array1(0, 0) = 4;
  double res = array1.Determinant();
  ASSERT_NEAR(res, 4, EXP);
}

TEST(DeterminantMatrix, MatrixSqrTwo) {
  S21Matrix array1(2, 2);
  array1(0, 0) = 3;
  array1(0, 1) = 1;
  array1(1, 0) = 7;
  array1(1, 1) = 2;
  double res = array1.Determinant();
  ASSERT_NEAR(res, -1, EXP);
}

TEST(DeterminantMatrix, MatrixSqrThree) {
  S21Matrix array1(3, 3);
  array1(0, 0) = 5;
  array1(0, 1) = 1;
  array1(0, 2) = -2;
  array1(1, 0) = 7;
  array1(1, 1) = -8;
  array1(1, 2) = 2;
  array1(2, 0) = 1;
  array1(2, 1) = -6;
  array1(2, 2) = 2;
  double res = array1.Determinant();
  ASSERT_NEAR(res, 36, EXP);
}

TEST(DeterminantMatrix, MatrixSqrFour) {
  S21Matrix array1(4, 4);
  array1(0, 0) = 5;
  array1(0, 1) = 1;
  array1(0, 2) = -2;
  array1(0, 3) = 12;
  array1(1, 0) = 7;
  array1(1, 1) = -8;
  array1(1, 2) = 2;
  array1(1, 3) = -22;
  array1(2, 0) = 1;
  array1(2, 1) = -6;
  array1(2, 2) = 2;
  array1(2, 3) = 15;
  array1(3, 0) = 24;
  array1(3, 1) = -7;
  array1(3, 2) = -12;
  array1(3, 3) = 5;
  double res = array1.Determinant();
  ASSERT_NEAR(res, -15264, EXP);
}

TEST(Inverse_matrix, True) {
  S21Matrix array1(3, 3);
  array1(0, 0) = 2;
  array1(0, 1) = 5;
  array1(0, 2) = 7;
  array1(1, 0) = 6;
  array1(1, 1) = 3;
  array1(1, 2) = 4;
  array1(2, 0) = 5;
  array1(2, 1) = -2;
  array1(2, 2) = -3;

  S21Matrix array2 = array1.InverseMatrix();

  S21Matrix array3(3, 3);
  array3(0, 0) = 1;
  array3(0, 1) = -1;
  array3(0, 2) = 1;
  array3(1, 0) = -38;
  array3(1, 1) = 41;
  array3(1, 2) = -34;
  array3(2, 0) = 27;
  array3(2, 1) = -29;
  array3(2, 2) = 24;
  ASSERT_TRUE(array2 == array3);
}

TEST(OperatorSumReplaceMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  array1 += array2;
  ASSERT_NEAR(1.2, array1(0, 0), EXP);
  ASSERT_NEAR(0.0, array1(0, 1), EXP);
  ASSERT_NEAR(2.5, array1(1, 0), EXP);
  ASSERT_NEAR(0.0, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(OperatorSumMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  S21Matrix array3 = array1 + array2;
  ASSERT_NEAR(1.2, array3(0, 0), EXP);
  ASSERT_NEAR(0.0, array3(0, 1), EXP);
  ASSERT_NEAR(2.5, array3(1, 0), EXP);
  ASSERT_NEAR(0.0, array3(1, 1), EXP);
  ASSERT_EQ(2, array3.getRows());
  ASSERT_EQ(2, array3.getCols());
}

TEST(OperatorSubReplaceMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  array1 -= array2;
  ASSERT_NEAR(1.2, array1(0, 0), EXP);
  ASSERT_NEAR(0.0, array1(0, 1), EXP);
  ASSERT_NEAR(-2.5, array1(1, 0), EXP);
  ASSERT_NEAR(0.0, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(OperatorSubMatrix, CorrectInput) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 1.2;
  array2(1, 0) = 2.5;
  S21Matrix array3 = array1 - array2;
  ASSERT_NEAR(1.2, array3(0, 0), EXP);
  ASSERT_NEAR(0.0, array3(0, 1), EXP);
  ASSERT_NEAR(-2.5, array3(1, 0), EXP);
  ASSERT_NEAR(0.0, array3(1, 1), EXP);
  ASSERT_EQ(2, array3.getRows());
  ASSERT_EQ(2, array3.getCols());
}

TEST(OperatorMulReplaceMatrixByNumber, SingleTest) {
  S21Matrix array1(2, 2);
  array1(0, 0) = 2;
  array1(0, 1) = 1;
  array1(1, 0) = 4.2;
  array1(1, 1) = -3.2;
  array1 *= 2;
  ASSERT_NEAR(4, array1(0, 0), EXP);
  ASSERT_NEAR(2, array1(0, 1), EXP);
  ASSERT_NEAR(8.4, array1(1, 0), EXP);
  ASSERT_NEAR(-6.4, array1(1, 1), EXP);
  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(OperatorMulMatrixByNumber, SingleTest) {
  S21Matrix array1(2, 2);
  array1(0, 0) = 2;
  array1(0, 1) = 1;
  array1(1, 0) = 4.2;
  array1(1, 1) = -3.2;
  S21Matrix array3 = array1 * 2;
  ASSERT_NEAR(4, array3(0, 0), EXP);
  ASSERT_NEAR(2, array3(0, 1), EXP);
  ASSERT_NEAR(8.4, array3(1, 0), EXP);
  ASSERT_NEAR(-6.4, array3(1, 1), EXP);
  ASSERT_EQ(2, array3.getRows());
  ASSERT_EQ(2, array3.getCols());
}

TEST(OperatorMulReplaceMatrix, SqrMatrix) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 2;
  array1(0, 1) = 1;
  array1(1, 0) = 4.2;
  array1(1, 1) = -3.2;

  array2(0, 0) = 4;
  array2(0, 1) = 2;
  array2(1, 0) = -1;
  array2(1, 1) = -3;

  array1 *= array2;
  ASSERT_NEAR(7, array1(0, 0), EXP);
  ASSERT_NEAR(1, array1(0, 1), EXP);
  ASSERT_NEAR(20, array1(1, 0), EXP);
  ASSERT_NEAR(18, array1(1, 1), EXP);

  ASSERT_EQ(2, array1.getRows());
  ASSERT_EQ(2, array1.getCols());
}

TEST(OperatorMulMatrix, SqrMatrix) {
  S21Matrix array1(2, 2);
  S21Matrix array2(2, 2);
  array1(0, 0) = 2;
  array1(0, 1) = 1;
  array1(1, 0) = 4.2;
  array1(1, 1) = -3.2;

  array2(0, 0) = 4;
  array2(0, 1) = 2;
  array2(1, 0) = -1;
  array2(1, 1) = -3;

  S21Matrix array3 = array1 * array2;
  ASSERT_NEAR(7, array3(0, 0), EXP);
  ASSERT_NEAR(1, array3(0, 1), EXP);
  ASSERT_NEAR(20, array3(1, 0), EXP);
  ASSERT_NEAR(18, array3(1, 1), EXP);

  ASSERT_EQ(2, array3.getRows());
  ASSERT_EQ(2, array3.getCols());
}

TEST(OperatorBracket, SingleTest) {
  S21Matrix array1(2, 1);
  array1(0, 0) = 1;
  ASSERT_NEAR(1, array1(0, 0), EXP);
}

TEST(OperatorMulNumberByMatrix, SingleTest) {
  S21Matrix array1(2, 2);
  array1(0, 0) = 2;
  array1(0, 1) = 1;
  array1(1, 0) = 4.2;
  array1(1, 1) = -3.2;
  S21Matrix array3 = array1 * 2;
  ASSERT_NEAR(4, array3(0, 0), EXP);
  ASSERT_NEAR(2, array3(0, 1), EXP);
  ASSERT_NEAR(8.4, array3(1, 0), EXP);
  ASSERT_NEAR(-6.4, array3(1, 1), EXP);
  ASSERT_EQ(2, array3.getRows());
  ASSERT_EQ(2, array3.getCols());
}

TEST(EqMatrixTest, HanglesInitedEqualMatrices) {
  TestS21Matrix A, B;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(EqMatrixTest, HanglesInitedUnEqualMatrices) {
  TestS21Matrix A, B;
  B.matrix(0, 0) = A.matrix(0, 0) - 1;
  ASSERT_EQ(false, A.matrix.EqMatrix(B.matrix));
}

TEST(SumMatrixTest, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(4);
  A.matrix.SumMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(SubMatrixTest, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(1);
  A.matrix.SubMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(MulMatrixTest, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(3);
  A.matrix.MulMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(MulNumberTest, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(4);
  A.matrix.MulNumber(2);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(TransposeTest, HanglesInitedMatrices) {
  TestS21Matrix A(5);
  S21Matrix B = A.matrix.Transpose();
  ASSERT_EQ(true, B.EqMatrix(A.t_matrix));
}

TEST(CalcComplementsTest, HanglesInitedMatrices) {
  TestS21Matrix A;
  S21Matrix B = A.matrix.CalcComplements();
  ASSERT_EQ(true, B.EqMatrix(A.alg_matrix));
}

TEST(DeterminantTest, HanglesInitedMatrices3x3) {
  TestS21Matrix A(3);
  double determinant = A.matrix.Determinant();
  ASSERT_DOUBLE_EQ(determinant, 8649.0);
}

TEST(MoveConstructor, HanglesInitedMatrices) {
  S21Matrix A;
  A(0, 0) = 7;
  S21Matrix B(std::move(A));
  ASSERT_EQ(true, B(0, 0) == 7);
}

TEST(DeterminantTest, HanglesInitedMatrices4x4) {
  S21Matrix A(3, 3);
  A.operator()(0, 0) = 8;
  A.operator()(0, 1) = 2;
  A.operator()(0, 2) = 4;
  A.operator()(1, 0) = 4;
  A.operator()(1, 1) = 6;
  A.operator()(1, 2) = 6;
  A.operator()(2, 0) = 4;
  A.operator()(2, 1) = 8;
  A.operator()(2, 2) = 8;
  EXPECT_EQ(16, A.Determinant());
}

TEST(InverseMatrixTest, HanglesInitedMatrices3x3) {
  TestS21Matrix A;
  S21Matrix C = A.matrix.InverseMatrix();
  for (int i = 0; i < C.getRows(); i++) {
    for (int j = 0; j < C.getCols(); j++) {
      std::cout << C(i, j) << "\t";
    }
    std::cout << std::endl;
  }
  ASSERT_EQ(true, C.EqMatrix(A.i_matrix));
}

TEST(OperatorEqual, HanglesInitedMatrices) {
  TestS21Matrix A, B;
  bool status = false;
  if (A.matrix == B.matrix) {
    status = true;
  }
  ASSERT_EQ(true, status);
}

TEST(OpetatorCopy, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(1);
  B.matrix = A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorSum, HanglesInitedMatrices) {
  TestS21Matrix A, B;
  A.matrix += B.matrix;
  B.matrix *= 2;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorSub, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(1);
  A.matrix -= A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorPlus, HanglesInitedMatrices) {
  TestS21Matrix A, B;
  A.matrix = A.matrix + A.matrix;
  B.matrix *= 2;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorMinus, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(1);
  A.matrix = A.matrix - A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorMulMatrices, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(3);
  A.matrix *= A.matrix;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OpetatorStar, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(3);
  A.matrix = A.matrix * A.matrix;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OperatorStar2, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(4);
  A.matrix = A.matrix * 2;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OpetatorMulNum, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(4);
  A.matrix *= 2;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(SetColRow, HanglesInitedMatrices) {
  TestS21Matrix A;
  TestS21Matrix B(0);
  A.matrix.setCols(2);
  A.matrix.setRows(2);
  ASSERT_EQ(true, A.matrix == B.matrix);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}