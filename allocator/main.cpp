#include "allocator.hpp"
#include "container.hpp"

#include <iostream>
#include <map>

int factorial(int x)
{
  if (x > 1) return x * factorial(x - 1);
  else return 1;
}

int main()
{
  /* std::map with std::allocator */
  {
    auto m = std::map<int, int>{};

    for( int i = 0; i < 10; ++i )
      m.emplace(i, factorial(i));
    for( int i = 0; i < 10; ++i )
      std::cout << m[i] << "\n";
  }
  std::cout << "**********************\n";

  /* std::map with Allocator */
  {
    auto m = std::map<
      int,
      int,
      std::less<int>,
      Allocator<
        std::pair<
          const int,
          int
        >,
        10
      >
    >{};

    for( int i = 0; i < 10; ++i )
      m.emplace(i, factorial(i));
    for( int i = 0; i < 10; ++i )
      std::cout << m[i] << "\n";
  }
  std::cout << "**********************\n";

  /* List with std::allocator */
  {
    auto list = List<
      int
    >{};

    for( int i = 0; i < 10; ++i )
      list.push_back(factorial(i));
    for( auto it = list.begin(); it != list.end(); ++it )
      std::cout << *it << "\n";
  }
  std::cout << "**********************\n";

  /* List with Allocator */
  {
    auto list = List<
      int,
      Allocator<
        int,
        10
      >
    >{};

    for( int i = 0; i < 10; ++i )
      list.push_back(factorial(i));
    for( auto it = list.begin(); it != list.end(); ++it )
      std::cout << *it << "\n";
  }

  return 0;
}
