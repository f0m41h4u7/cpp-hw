#pragma once

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

/*
 * \brief Converts an integral value to unsigned.
 * \param t - integral value.
 */
template<typename T>
auto to_unsigned(const T& t) { return std::make_unsigned_t<T>(t); }

/*
 * \brief Checks if type is specialization.
 */
template< typename T, template<typename...> typename U >
struct is_specialization : std::false_type {};

/*
 * \brief Checks if type is specialization.
 */
template< template<typename...> typename T, typename... Args >
struct is_specialization<T<Args...>, T>: std::true_type {};

/*
 * \brief Checks if type is integral.
 */
template< typename T >
using is_int = std::enable_if_t< std::is_integral_v< T >, bool >;

/*
 * \brief Checks if type is std::string.
 */
template< typename T >
using is_string = std::enable_if_t< std::is_same_v< T, std::string >, bool >;

/*
 * \brief Checks if type is std::list or std::vector.
 */
template< typename T >
using is_container = std::enable_if_t< (is_specialization< T, std::list >::value || is_specialization< T, std::vector >::value), bool >;

/*
 * \brief Prints IP address provided in integral form.
 * \param ip - IP address value in integral form.
 */
template < typename T, is_int<T> = true >
void print_ip(const T& ip)
{
  char ip_str[INET_ADDRSTRLEN];
  auto tmp = htonl(ip);
  inet_ntop(AF_INET, &tmp, ip_str, INET_ADDRSTRLEN);
  std::cout << ip_str;
}

/*
 * \brief Prints IP address provided in string form.
 * \param ip - IP address value in string form.
 */
template < typename T, is_string<T> = true >
void print_ip(const T& ip)
{
  std::cout << ip;
}

/*
 * \brief Prints IP address passed in std::list or std::vector container.
 * \param ip - container with IP address value.
 */
template < typename T, is_container<T> = true >
void print_ip(const T& ip)
{
  for(auto it = ip.begin(); it != ip.end();)
  {
    std::cout << +(to_unsigned(*it));
    if(++it != ip.end())
      std::cout << ".";
  }
}
