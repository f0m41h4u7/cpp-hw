#include <iostream>

#include "Matrix.hpp"

int main()
{
  Matrix<int, 0> matrix;

  int j = 9;
  for(int i = 0; i < 10; ++i)
  {
    matrix[i][j] = j;
    matrix[i][i] = i;
    --j;
  }

  for(int i = 1; i < 9; ++i)
  {
    for(j = 1; j < 9; ++j)
    {
      std::cout << matrix[i][j];
      if (j!=8) std::cout << " ";
    }
    std::cout << "\n";
  }
    
  std::cout << "\n" << matrix.size() << "\n\n";
    
  for(auto& c : matrix)
  {
      int x, y, v;
      std::tie(x, y, v) = c;
      std::cout << "matrix[" << x << "][" << y << "] =  " << v << "\n";
  }
  
  return 0;
}
