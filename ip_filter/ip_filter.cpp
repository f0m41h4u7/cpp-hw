#include "ip_filter.hpp"

#include <iostream>

uint32_t IP_filter::parseIP(std::string_view line)
{
  // find IPv4 address in string
  if (std::regex_search (line.data(), m_match, IPv4Regex)) {
    // convert IP address to binary representation
    if (!inet_pton(AF_INET, m_match.str(0).c_str(), &m_tmp)) return 0;
  }
  else return 0;
    
  return ntohl(m_tmp);
}

void IP_filter::printReverse()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    m_tmp = htonl(*ip);
    inet_ntop(AF_INET, &m_tmp, m_IP_str, INET_ADDRSTRLEN);
    std::cout << m_IP_str << "\n";
  }
}

void IP_filter::printOneInFirstByte()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    m_tmp = htonl(*ip);
    if ( (m_tmp & 0xff) == 1)
    {
      inet_ntop(AF_INET, &m_tmp, m_IP_str, INET_ADDRSTRLEN);
      std::cout << m_IP_str << "\n";
    }
  }
}

void IP_filter::print46And70Bytes()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    m_tmp = htonl(*ip);
    if ( ((m_tmp & 0xff) == 46) && (((m_tmp >> 8) & 0xff) == 70) )
    {
      inet_ntop(AF_INET, &m_tmp, m_IP_str, INET_ADDRSTRLEN);
      std::cout << m_IP_str << "\n";
    }
  }
}

void IP_filter::print46InAnyByte()
{
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    m_tmp = htonl(*ip);
    for(auto i = 0; i < 4; ++i)
    {
      if ( ((m_tmp >> (8*i)) & 0xff) == 46 )
      {
        inet_ntop(AF_INET, &m_tmp, m_IP_str, INET_ADDRSTRLEN);
        std::cout << m_IP_str << "\n";
        break;
      }
    }
  }
}
