#include <Graph_lib/Graph.hpp>
#include <Graph_lib/Simple_window.hpp>
#include <cstdlib>

auto main() -> int {
  using namespace Graph_lib;

  Simple_window win{Point{100, 100}, 600, 400, "Canvas"};

  // Section 13.3
  Lines lines;
  lines.add(Point{100, 100}, Point{200, 100});
  lines.add(Point{150, 50}, Point{150, 150});
  win.attach(lines);
  win.set_label("Canvas #1");
  win.wait_for_button();

  int x_size = win.x_max();
  int y_size = win.y_max();
  int x_grid = 80;
  int y_grid = 80;

  Lines grid;
  for (int x = x_grid; x < x_size; x += x_grid)
    grid.add(Point{x, 0}, Point{x, y_size});
  for (int y = y_grid; y < y_size; y += y_grid)
    grid.add(Point{0, y}, Point{x_size, y});
  win.attach(grid);
  win.set_label("Canvas #2");
  win.wait_for_button();

  // Section 13.4
  grid.set_color(Color::red);
  win.wait_for_button();

  return EXIT_SUCCESS;
}
