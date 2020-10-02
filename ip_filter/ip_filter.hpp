#include <arpa/inet.h>
#include <regex>
#include <set>
#include <string_view>

const std::regex IPv4Regex("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");

struct IP_filter
{
  IP_filter() {}

  void appendIP(uint32_t ip) { m_IP_addrs.insert(ip); }

  uint32_t parseIP(std::string_view);
  void printReverse();
  void printMatchRegex(std::string_view);

private:
  std::multiset<uint32_t> m_IP_addrs;
  char               m_IP_str[INET_ADDRSTRLEN];
  uint32_t           m_tmp;
  std::cmatch        m_match;
};
