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

void IP_filter::printMatchRegex(std::string_view reg_sv)
{
  std::regex reg(reg_sv.data());
  for(auto ip = m_IP_addrs.rbegin(); ip != m_IP_addrs.rend(); ++ip)
  {
    m_tmp = htonl(*ip);
    inet_ntop(AF_INET, &m_tmp, m_IP_str, INET_ADDRSTRLEN);
    if (std::regex_match (m_IP_str, m_match, reg))
    {
      std::cout << m_IP_str << "\n";
    }    
  }
}
