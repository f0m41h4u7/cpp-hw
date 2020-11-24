#include "print_ip.hpp"

#include <list>
#include <string>
#include <vector>

int main()
{
  using namespace std::string_literals;
  print_ip<char>(-1);
  std::cout << "\n";

  print_ip<short>(0);
  std::cout << "\n";

  print_ip<int>(2130706433);
  std::cout << "\n";

  print_ip<long>(8875824491850138409);
  std::cout << "\n";

  print_ip("43.98.123.7"s);
  std::cout << "\n";

  std::vector<int> ip_vec{98, 32, 124, 78};
  print_ip(ip_vec);
  std::cout << "\n";

  std::list<int> ip_list{88, 213, 121, 123};
  print_ip(ip_list);

  return 0;
}
