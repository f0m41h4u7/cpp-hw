#pragma once

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include <regex>
#include <set>
#include <string_view>

const std::regex IPv4Regex("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");

struct IP_filter
{
  IP_filter() {}

  int append(std::string_view);
  void printReverse();
  void printOneInFirstByte();
  void print46And70Bytes();
  void print46InAnyByte();

private:
  std::multiset<uint32_t> m_IP_addrs;
  char                    m_IP_str[INET_ADDRSTRLEN];
};
