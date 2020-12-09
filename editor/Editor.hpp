#pragma once

#include <vector>

#include "Controller.hpp"

class Editor
{
public:
  Editor() = default;
  ~Editor() = default;

  Controller* open()
  {
    m_controllers.emplace_back(std::make_unique<Controller>());
    return m_controllers.back().get();
  }

private:
  std::list<std::unique_ptr<Controller>> m_controllers;
};
