#pragma once

#include <array>
#include <cmath>
#include <memory>

#include "View.hpp"

using Point = std::pair<int, int>;

class Shape
{
public:
  Shape() = default;
  virtual ~Shape(){}

  virtual void draw(View* view) = 0;
  virtual void erase(View* view) = 0;
  virtual bool has_coord(Point p) const = 0;
};

class Triangle : public Shape
{
public:
  Triangle(std::array<Point, 3>& points) : m_points(std::move(points)) {}
  ~Triangle() = default;

  void draw(View* view) override
  {
    view->draw_line(m_points[0], m_points[1]);
    view->draw_line(m_points[0], m_points[2]);
    view->draw_line(m_points[1], m_points[2]);
  }

  void erase(View* view) override
  {
    view->erase_line(m_points[0], m_points[1]);
    view->erase_line(m_points[0], m_points[2]);
    view->erase_line(m_points[1], m_points[2]);
  }

  bool has_coord(Point p) const override
  {
    auto d1 = (p.first - m_points[1].first) * (m_points[0].second - m_points[1].second) - (m_points[0].first - m_points[1].first) * (p.second - m_points[1].second);
    auto d2 = (p.first - m_points[2].first) * (m_points[1].second - m_points[2].second) - (m_points[1].first - m_points[2].first) * (p.second - m_points[2].second);
    auto d3 = (p.first - m_points[0].first) * (m_points[2].second - m_points[0].second) - (m_points[2].first - m_points[0].first) * (p.second - m_points[0].second);

    auto has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    auto has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
  }

private:
  std::array<Point, 3> m_points;
};
