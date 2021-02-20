#include <iostream>

#include "async.hpp"

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    std::cout << "block size and port are required as arguments\n";
    return 1;
  }

  int n = 0;
  short unsigned int port = 0;
  if(!sscanf(argv[1], "%d", &n))
  {
    std::cout << "argument should be int\n";
    return 1;
  }
  if(!sscanf(argv[2], "%hu", &port))
  {
    std::cout << "argument should be short unsigned int\n";
    return 1;
  }
  
  async_blk::run_server(n, port);

  return 0;
}
