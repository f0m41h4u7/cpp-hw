#pragma once

#include <memory>
#include <list>
#include <iterator>
#include <string_view>

#include "Shape.hpp"

class Model
{
public:
  Model() = default;
  ~Model() = default;

  void new_view()
  {
    if (!m_is_opened)
    {
      m_view = std::make_unique<View>();
      m_is_opened = true;
      std::cout << "opened\n";
    }
  }

  void new_view(std::string_view fname)
  {
    if (!m_is_opened)
    {
      new_view();
      std::cout << "imported from " << fname.data() << "\n";
    }
  }

  void save(std::string_view fname)
  {
    if (m_is_opened)
    {
      std::cout << "saved to " << fname.data() << "\n";
    }
  }

  template <typename S, typename... Args>
  void draw_shape(Args&&... args)
  {
    if (m_is_opened)
    {
      m_shapes.emplace_back(std::make_unique<S>(std::forward<Args>(args)...));
      m_shapes.back()->draw(m_view.get());
      std::cout << "draw shape\n";
    }
  }

  void erase()
  {
    if (m_is_opened && (m_selected != m_shapes.end()))
    {
      (*m_selected)->erase(m_view.get());
      m_shapes.erase(m_selected);
      m_selected = m_shapes.end();
      std::cout << "erase shape\n";
    }
  }

  bool select(std::pair<int, int> coord)
  {
    if (m_is_opened)
    {
      for(auto it = m_shapes.begin(); it != m_shapes.end(); ++it)
      {
        if((*it)->has_coord(coord))
        {
          m_selected = it;
          std::cout << "selected shape\n";
          return 1;
        }
      }
    }
    return 0;
  }

  void close()
  {
    if (m_is_opened)
    {
      m_is_opened = false;
      m_shapes.clear();
      m_selected = m_shapes.end();
      std::cout << "closed\n";
    }
  }

private:
  std::list<std::unique_ptr<Shape>>           m_shapes;
  std::unique_ptr<View>                       m_view {nullptr};
  std::list<std::unique_ptr<Shape>>::iterator m_selected {m_shapes.end()};
  bool                                        m_is_opened {false};
};
