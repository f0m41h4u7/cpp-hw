#pragma once

#include <iostream>
#include <utility>

class View
{
public:
  View() = default;
  ~View() = default;

  void draw_line(std::pair<int, int> p1, std::pair<int, int> p2)
  {
    std::cout << "draw line at (" << p1.first << "," << p1.second << "); ("
      << p2.first << "," << p2.second << ")\n";
  }

  void erase_line(std::pair<int, int> p1, std::pair<int, int> p2)
  {
    std::cout << "erase line at (" << p1.first << "," << p1.second << "); ("
      << p2.first << "," << p2.second << ")\n";
  }
};
