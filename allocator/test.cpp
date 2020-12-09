#define BOOST_TEST_MODULE allocator_test
  
#include "allocator.hpp"
#include "container.hpp"

#include <boost/test/unit_test.hpp>
#include <map>

BOOST_AUTO_TEST_SUITE(allocator_test)
BOOST_AUTO_TEST_CASE(test_allocator)
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
      3
    >
  >{};

  for( int i = 0; i < 3; ++i ) m.emplace(i, i+1);
  BOOST_CHECK(m[0] == 1);
  BOOST_CHECK(m[1] == 2);
  BOOST_CHECK(m[2] == 3);
}

BOOST_AUTO_TEST_CASE(test_list)
{
  auto list = List<
    int,
    Allocator<
      int,
      3
    >
  >{};

  for( int i = 0; i < 3; ++i ) list.push_back(i+1);

  BOOST_CHECK(list.size() == 3);

  auto it = list.begin();
  BOOST_CHECK(*it == 1);
  BOOST_CHECK(*(++it) == 2);
  BOOST_CHECK(*(++it) == 3);
}

}
