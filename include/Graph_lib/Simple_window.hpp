
#include <Graph_lib/GUI.hpp> // for Simple_window only (doesn't really belong in Window.hpp)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window : Window {
  Simple_window(Point xy, int w, int h, const string &title)
      : Window(xy, w, h, title),
        next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
        button_pushed(false) {
    attach(next_button);
  }

  bool wait_for_button();

  Button next_button;

private:
  bool button_pushed;

  static void cb_next(Address, Address addr); // callback for next_button

  void next();
};
