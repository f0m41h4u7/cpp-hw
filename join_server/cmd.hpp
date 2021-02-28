#pragma once

#include <tao/pegtl.hpp>
#include <tuple>

#include "storage.hpp"

namespace cmd
{
  enum class operation
  {
    INSERT,
    TRUNCATE,
    INTERSECT,
    SYMDIF
  };
  
  constexpr std::string_view success_result = "OK\n";
  constexpr std::string_view parse_error = "ERR failed to parse command\n";
  constexpr std::string_view duplicate_error = "ERR duplicate ";
  constexpr std::string_view table_error = "ERR wrong table id\n";
  constexpr std::string_view unknown_error = "ERR unknown\n";
  
  using namespace tao::pegtl;
  
  struct table_id : pad< ascii::upper, ascii::blank>{};
  
  struct id : pad< plus<ascii::digit>, ascii::blank>{};
  
  struct field : pad< plus<alpha>, ascii::blank>{};
  
  struct insert : seq<
    pad< string< 'I','N','S','E','R','T' >, ascii::blank>,
    table_id,
    id,
    field
  >{};
  
  struct truncate : seq<
    pad< string< 'T','R','U','N','C','A','T','E' >, ascii::blank>,
    table_id
  >{};
  
  struct intersect : pad< string< 'I','N','T','E','R','S','E','C','T','I','O','N' >, ascii::blank>{};
  struct symdif : pad< string< 'S','Y','M','M','E','T','R','I','C','_','D','I','F','F','E','R','E','N','C','E' >, ascii::blank>{};
  
  struct command : sor< insert, truncate, intersect, symdif >{};
  
  template< typename Rule >
  struct action
  {};
  
  template<>
  struct action< insert >
  {
    template< class T, class C >
    static void apply(const T&, C& ctx)
    {
      std::get<0>(ctx) = operation::INSERT;
    }
  };
  
  template<>
  struct action< truncate >
  {
    template< class T, class C >
    static void apply(const T&, C& ctx)
    {
      std::get<0>(ctx) = operation::TRUNCATE;
    }
  };
  
  template<>
  struct action< intersect >
  {
    template< class T, class C >
    static void apply(const T&, C& ctx)
    {
      std::get<0>(ctx) = operation::INTERSECT;
    }
  };
  
  template<>
  struct action< symdif >
  {
    template< class T, class C >
    static void apply(const T&, C& ctx)
    {
      std::get<0>(ctx) = operation::SYMDIF;
    }
  };

  template<>
  struct action< table_id >
  {
    template< class T, class C >
    static void apply(const T& in, C& ctx)
    {
      std::get<1>(ctx) = in.string();
    }
  };
  
  template<>
  struct action< id >
  {
    template< class T, class C >
    static void apply(const T& in, C& ctx)
    {
      std::get<2>(ctx) = std::stoi(in.string());
    }
  };
  
  template<>
  struct action< field >
  {
    template< class T, class C >
    static void apply(const T& in, C& ctx)
    {
      std::get<3>(ctx) = in.string();
    }
  };
  
} // namespace cmd
