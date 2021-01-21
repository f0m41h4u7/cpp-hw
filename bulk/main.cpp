#include <iostream>

#include "bulk.hpp"

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    std::cout << "require block size as argument\n";
    return 1;
  }

  int n = 0;
  if(!sscanf(argv[1], "%d", &n))
  {
    std::cout << "argument should be int\n";
    return 1;
  }

  std::string line;
  bulk bulk(n);

  while(std::getline(std::cin, line))
    bulk.add(line);

  bulk.print();

  return 0;
}
