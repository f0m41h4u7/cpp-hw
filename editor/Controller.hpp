#pragma once

#include "Model.hpp"

class Controller
{
public:
  Controller()
  {
    m_model = std::make_unique<Model>();
    std::cout << "model created\n";
  }

  ~Controller() = default;

  void create()
  {
    m_model->new_view();
  }

  void create(std::string_view fname)
  {
    m_model->new_view(fname);
  }

  void save(std::string_view fname)
  {
    m_model->save(fname);
  }

  void draw_triangle(std::array<Point, 3>& points)
  {
    m_model->draw_shape<Triangle>(points);
  }

  bool erase(std::pair<int, int>& coord)
  {
    if(m_model->select(coord))
    {
      m_model->erase();
      return 1;
    }
    return 0;
  }

  void close()
  {
    m_model->close();
  }

private:
  std::unique_ptr<Model> m_model;
};
