#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "Clock.h"
#include <glibmm/optioncontext.h>
#include <glibmm/optiongroup.h>
#include <glibmm/optionentry.h>

using std::string;

int main(int argc, char *argv[])
{
//  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
//
//  Gtk::Window window;
//  window.set_default_size(800, 600);
//
//  return app->run(window);

//  auto app = Gtk::Application::create(argc, argv, "kaz.clock.example");
//  Gtk::Window win;
//  win.set_title("Cairomm Clock");
//
//  Clock c;
//  win.add(c);
//  c.show();
//
//  return app->run(win);
  Glib::OptionContext context(nullptr);
  Glib::OptionEntry entry = {};
  Glib::OptionGroup optionGroup;
  optionGroup.add_entry(entry);
  context.add_group(optionGroup);
  string term = "xterm-termite";
}
