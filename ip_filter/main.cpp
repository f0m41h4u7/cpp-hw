#include "ip_filter.cpp"

#include <string>

int main()
{
  using namespace std::literals;

  std::string read_line;
  IP_filter f;

  while (std::getline(std::cin, read_line))
  {
    if (!f.append(std::string_view{read_line}))
    {
      std::cout << "failed to convert IPv4 address from line: \"" << read_line << "\"\n";
      return 1;
    }
  }
  
  // print reverse-sorted
  f.printReverse();

  // print IPs with 1 in first byte
  f.printOneInFirstByte();

  // print IPs with 46 in first byte and 70 in second byte
  f.print46And70Bytes();

  // print IPs with 46 in any byte
  f.print46InAnyByte();

  return 0;
}
