#include "Matrix.hpp"

#include <gtest/gtest.h>

TEST(MatrixTest, SimpleCase)
{ 
  Matrix<int, 61> matrix;
  auto x = matrix[0][9];
  ASSERT_EQ(61, x);
  ASSERT_EQ(0, matrix.size());

  matrix[1][2] = 2121;
  matrix[1][1] = 1212;
  ASSERT_EQ(2121, matrix[1][2]);
  ASSERT_EQ(1212, matrix[1][1]);
  ASSERT_EQ(2, matrix.size());

  matrix[1][2] = 0;
  ASSERT_EQ(0, matrix[1][2]);
  ASSERT_EQ(2, matrix.size());
}

TEST(MatrixTest, Iteration)
{
  Matrix<int, -4> matrix;
  for(int i = 0; i < 100; ++i)
    matrix[i][i] = i;
  for(int i = 0; i < 100; ++i)
    ASSERT_EQ(i, matrix[i][i]);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();        
}
