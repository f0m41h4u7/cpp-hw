#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct bulk
{
  bulk(int n) : m_default_size(n) { m_data.resize(n); }
  ~bulk() = default;

  void add(std::string_view line)
  {
    if(line == "{")
    {
      if(!m_block_started)
      {
        m_block_started = true;
        print();
      }
      return;
    }
    
    if(line == "}")
    {
      if(m_block_started)
      {
        m_block_started = false;
        print();
      }
      return;
    }

    if(m_counter >= m_default_size) m_data.push_back(line.data());
    else m_data[m_counter] = line.data();
    m_counter++;
    
    if(!m_block_started)
    {
      if(m_counter == m_default_size)
        print();
    }
  }

  void print()
  {
    if(m_counter == 0) return;
    std::cout << "bulk: ";
    for(int i = 0; i < m_counter; ++i)
    {
      std::cout << m_data[i];
      if(i != m_counter-1) std::cout << ", ";                      
    }
    std::cout << "\n";
    m_counter = 0;
  }

private:
  int                      m_default_size{1};
  int                      m_counter{0};
  bool                     m_block_started{false};
  std::vector<std::string> m_data;
};
