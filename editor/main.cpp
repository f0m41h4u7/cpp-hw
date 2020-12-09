#include "Editor.hpp"

int main()
{
  auto editor = new Editor();
  auto controller = editor->open();
  controller->create();

  std::array<Point, 3> points {
    std::pair<int, int>(0, 0),
    std::pair<int, int>(6, 6),
    std::pair<int, int>(1, 7)
  };
  controller->draw_triangle(points);
  controller->erase(points[0]);

  controller->save("new_picture.png");

  return 0;
}
