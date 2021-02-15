#include <iostream>

#include "async.hpp"

int main()//int argc, char** argv)
{
  /*
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

  bulk.print();*/
  
  auto handler = async_blk::connect(3);
  
  async_blk::receive(handler, "cmd1\ncmd2");
  async_blk::receive(handler, "cmd3\ncmd4\ncmd5");
  async_blk::receive(handler, "cmd6\ncmd7");
  
  async_blk::disconnect(handler);
  delete handler;
  
  return 0;
}
