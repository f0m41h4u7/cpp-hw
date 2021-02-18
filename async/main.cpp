#include "async.hpp"

int main()
{ 
  auto handler = async_blk::connect(3);
  
  async_blk::receive(handler, "cmd1\ncmd2");
  async_blk::receive(handler, "cmd3\ncmd4\ncmd5");
  async_blk::receive(handler, "cmd6\ncmd7");
  
  async_blk::disconnect(handler);
  delete handler;
  
  return 0;
}
