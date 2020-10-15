#include "ip_filter.hpp"

#include <iostream>

int IP_filter::append(std::string_view line)
{
  std::cmatch match;
  uint32_t tmp;
  // find IPv4 address in string
  if (std::regex_search (line.data(), match, IPv4Regex)) {
    // convert IP address to binary representation
    if (!inet_pton(AF_INET, match.str(0).c_str(), &tmp)) return 0;
  }
  else return 0;
  m_IP_addrs.insert(ntohl(tmp));
  return 1;
}

void IP_filter::printReverse()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    auto tmp = htonl(*ip);
    inet_ntop(AF_INET, &tmp, m_IP_str, INET_ADDRSTRLEN);
    std::cout << m_IP_str << "\n";
  }
}

void IP_filter::printOneInFirstByte()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    auto tmp = htonl(*ip);
    if ( (tmp & 0xff) == 1)
    {
      inet_ntop(AF_INET, &tmp, m_IP_str, INET_ADDRSTRLEN);
      std::cout << m_IP_str << "\n";
    }
  }
}

void IP_filter::print46And70Bytes()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    auto tmp = htonl(*ip);
    if ( ((tmp & 0xff) == 46) && (((tmp >> 8) & 0xff) == 70) )
    {
      inet_ntop(AF_INET, &tmp, m_IP_str, INET_ADDRSTRLEN);
      std::cout << m_IP_str << "\n";
    }
  }
}

void IP_filter::print46InAnyByte()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    auto tmp = htonl(*ip);
    for(auto i = 0; i < 4; ++i)
    {
      if ( ((tmp >> (8*i)) & 0xff) == 46 )
      {
        inet_ntop(AF_INET, &tmp, m_IP_str, INET_ADDRSTRLEN);
        std::cout << m_IP_str << "\n";
        break;
      }
    }
  }
}
