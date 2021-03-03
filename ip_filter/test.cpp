#define BOOST_TEST_MODULE ip_filter_test
  
#include "ip_filter.cpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include <streambuf>

BOOST_AUTO_TEST_SUITE(ip_filter_test)
BOOST_AUTO_TEST_CASE(test_reverse_sort)
{
  IP_filter f;
  int res;
  res = f.append("9.234.123.11");
  BOOST_CHECK(res != 0);

  res = f.append("1.234.123.11");
  BOOST_CHECK(res != 0);

  res = f.append("32.146.123.11");
  BOOST_CHECK(res != 0);

  res = f.append("3.46.123.21");
  BOOST_CHECK(res != 0);

  res = f.append("46.70.123.21");
  BOOST_CHECK(res != 0);

  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());
  f.printReverse();
  std::cout.rdbuf(coutBuf);

  BOOST_CHECK(strCout.str() == "46.70.123.21\n32.146.123.11\n9.234.123.11\n3.46.123.21\n1.234.123.11\n");
}

BOOST_AUTO_TEST_CASE(test_print_match)
{
  IP_filter f;
  int res;

  res = f.append("1.45.13.23");
  BOOST_CHECK(res != 0);

  res = f.append("1.234.123.11");
  BOOST_CHECK(res != 0);

  res = f.append("32.146.123.11");
  BOOST_CHECK(res != 0);

  res = f.append("3.46.123.21");
  BOOST_CHECK(res != 0);

  res = f.append("46.70.123.21");
  BOOST_CHECK(res != 0);

  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;

  std::cout.rdbuf(strCout.rdbuf());
  f.printOneInFirstByte();
  f.print46And70Bytes();
  f.print46InAnyByte();
  std::cout.rdbuf(coutBuf);

  BOOST_CHECK(strCout.str() == "1.234.123.11\n1.45.13.23\n46.70.123.21\n46.70.123.21\n3.46.123.21\n");
}


}
