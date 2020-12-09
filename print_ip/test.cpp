#define BOOST_TEST_MODULE print_ip_test
  
#include "print_ip.hpp"

#include <boost/test/unit_test.hpp>
#include <list>
#include <string>
#include <vector>

BOOST_AUTO_TEST_SUITE(print_ip_test)
BOOST_AUTO_TEST_CASE(test_integral)
{
  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  print_ip<char>(-1);
  std::cout<<" ";
  print_ip<short>(0);
  std::cout<<" ";
  print_ip<int>(2130706433);
  std::cout<<" ";
  print_ip<long>(8875824491850138409);

  std::cout.rdbuf(coutBuf);
  BOOST_CHECK(strCout.str() == "255.255.255.255 0.0.0.0 127.0.0.1 101.112.131.41");
}

BOOST_AUTO_TEST_CASE(test_string)
{
  using namespace std::string_literals;
  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  print_ip("43.98.123.7"s);

  std::cout.rdbuf(coutBuf);
  BOOST_CHECK(strCout.str() == "43.98.123.7");
}

BOOST_AUTO_TEST_CASE(test_containers)
{
  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  std::vector<int> ip_vec{98, 32, 124, 78};
  print_ip(ip_vec);
  std::cout<<" ";
  std::list<int> ip_list{88, 213, 121, 123};
  print_ip(ip_list);
  
  std::cout.rdbuf(coutBuf);
  BOOST_CHECK(strCout.str() == "98.32.124.78 88.213.121.123");
}

}
