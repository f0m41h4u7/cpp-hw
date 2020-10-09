#include "ip_filter.cpp"

#include <string>

int main()
{
  using namespace std::literals;

  std::string read_line;
  IP_filter f;
  uint32_t tmp;

  while (std::getline(std::cin, read_line))
  {
    tmp = f.parseIP(std::string_view{read_line});
    if (tmp == 0)
    {
      std::cout << "failed to convert IPv4 address from line: \"" << read_line << "\"\n";
      return 1;
    }
    f.appendIP(tmp);
  }
  
  // print reverse-sorted
  f.printReverse();

  // print IPs with 1 in first byte
  f.printMatchRegex("1\\.((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){2}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);

  // print IPs with 46 in first byte and 70 in second byte
  f.printMatchRegex("46\\.70\\.((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.)(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);

  // print IPs with 46 in any byte
  f.printMatchRegex("(?=[^12]*46.*)(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"sv);

  return 0;
}
