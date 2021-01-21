#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "bulk.hpp"

TEST(BulkTest, Brackets)
{
  bulk bulk(3);
  
  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());
  
  bulk.add("{");
  bulk.add("cmd1");
  bulk.add("cmd2");
  bulk.add("{");
  bulk.add("cmd3");
  bulk.add("cmd4");
  bulk.add("}");
  bulk.add("}");
  bulk.add("cmd5");
  bulk.add("cmd6");
  bulk.add("cmd7");
  bulk.add("cmd8");
  bulk.print();
  
  std::cout.rdbuf(coutBuf);
  
  ASSERT_STREQ("bulk: cmd1, cmd2, cmd3, cmd4\nbulk: cmd5, cmd6, cmd7\nbulk: cmd8\n", strCout.str().c_str());
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();        
}
