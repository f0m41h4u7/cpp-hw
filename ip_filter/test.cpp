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
  uint32_t ip;
  ip = f.parseIP("9.234.123.11");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("1.234.123.11");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("32.146.123.11");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("3.46.123.21");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("46.70.123.21");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);

  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());
  f.printReverse();
  std::cout.rdbuf(coutBuf);

  BOOST_CHECK(strCout.str() == "46.70.123.21\n32.146.123.11\n9.234.123.11\n3.46.123.21\n1.234.123.11\n");
}

BOOST_AUTO_TEST_CASE(test_print_match)
{
  using namespace std::literals;

  IP_filter f;
  uint32_t ip;
  ip = f.parseIP("1.45.13.23");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("1.234.123.11");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("32.146.123.11");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("3.46.123.21");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);
  ip = f.parseIP("46.70.123.21");
  BOOST_CHECK(ip != 0);
  f.appendIP(ip);

  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;

  std::cout.rdbuf(strCout.rdbuf());
  f.printMatchRegex("1\\.((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){2}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);
  f.printMatchRegex("46\\.70\\.((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.)(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);
  f.printMatchRegex("(?=[^12]*46.*)(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);
  std::cout.rdbuf(coutBuf);

  BOOST_CHECK(strCout.str() == "1.234.123.11\n1.45.13.23\n46.70.123.21\n46.70.123.21\n3.46.123.21\n");
}


}
