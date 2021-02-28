#pragma once

#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>

namespace db
{
  constexpr std::string_view comma_token = ",";
  constexpr std::string_view newline_token = "\n";
  
  class table
  {
  public:
    table() = default;
    ~table() = default;
    
    int insert(std::size_t id, std::string_view field)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      if(m_data.contains(id))
        return 1;
      
      m_data[id] = field;
      return 0;
    }
    
    void truncate()
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_data.clear();
    }
    
    std::mutex                         m_mutex;
    std::map<std::size_t, std::string> m_data;
  };
  
  template <std::size_t N = 2>
  class storage
  {
  public:
    storage() = default;
    ~storage() = default;
    
    // returns -1 if table_id is wrong, 1 if duplicate id, 0 if ok
    int insert(std::size_t table_id, std::size_t id, std::string& field)
    {
      if(table_id >= N)
        return -1;
      
      return m_tables[table_id].insert(id, field);
    }
    
    // returns 1 if table_id is wrong, 0 if ok
    int truncate(std::size_t table_id)
    {
      if(table_id >= N)
        return 1;
      
      m_tables[table_id].truncate();
      return 0;
    }
    
    std::string intersect()
    {
      std::stringstream stream;
      for(auto& t : m_tables[0].m_data)
      {
        if(m_tables[1].m_data.contains(t.first))
          stream << t.first << comma_token << t.second << comma_token << m_tables[1].m_data[t.first] << newline_token;
      }
      return stream.str();
    }
    
    std::string symdif()
    {
      std::stringstream stream;
      for(auto& t : m_tables[0].m_data)
      {
        if(!m_tables[1].m_data.contains(t.first))
          stream << t.first << comma_token << t.second << comma_token << newline_token;
      }
      for(auto& t : m_tables[1].m_data)
      {
        if(!m_tables[0].m_data.contains(t.first))
          stream << t.first << comma_token << comma_token << t.second << newline_token;
      }
      return stream.str();
    }
    
  private:
    std::array<table, N> m_tables;
  };
} //namespace db
