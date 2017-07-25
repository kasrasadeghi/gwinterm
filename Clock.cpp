#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "Clock.h"

Clock::Clock() : _radius(0.42), _line_width(0.05) {
  Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &Clock::on_timeout), 1000
  );
}

Clock::~Clock() {}

bool Clock::on_draw(const Cairo::RefPtr<Cairo::Context>& g) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  //scale to the unit square and translate the context to be in the center
  g->scale(width, height);
  g->translate(0.5, 0.5);
  g->set_line_width(_line_width);

  g->save();
  g->set_source_rgba(0.337, 0.642, 0.117, 0.9);
  g->paint();
  g->restore();
  g->arc(0, 0, _radius, 0, 2 * M_PI);
  g->save();
  g->set_source_rgba(1.0, 1.0, 1.0, 0.8); // black
  g->fill_preserve();
  g->restore();
  g->stroke_preserve();
  g->clip();

  //clock ticks

  for (int i = 0; i < 12; ++i) {
    double inset = 0.05;

    g->save();
    g->set_line_cap(Cairo::LINE_CAP_ROUND);

    if (i % 3 != 0) {
      inset *= 0.8;
      g->set_line_width(0.03);
    }

    g->move_to(
        (_radius - inset) * cos(i * M_PI / 6),
        (_radius - inset) * sin(i * M_PI / 6)
    );

    g->line_to(
      _radius * cos(i * M_PI / 6),
      _radius * sin(i * M_PI / 6)
    );

    g->stroke();
    g->restore();
  }

  time_t rawtime;
  time(&rawtime);

  tm* timeinfo = localtime(&rawtime);

  // compute the angles of the indicators of our clock
  double minutes = timeinfo->tm_min  * M_PI / 30;
  double hours   = timeinfo->tm_hour * M_PI / 6;
  double seconds = timeinfo->tm_sec  * M_PI / 30;

  g->save();
  g->set_line_cap(Cairo::LINE_CAP_ROUND);

  // draw the seconds hand
  g->save();
  g->set_line_width(_line_width / 3);
  g->set_source_rgba(0.7, 0.7, 0.7, 0.8);
  g->move_to(0, 0);
  g->line_to(
      sin(seconds) * (_radius * 0.9),
     -cos(seconds) * (_radius * 0.9)
  );
  g->stroke();
  g->restore();

  // draw the hours hand
  g->set_source_rgba(0.117, 0.337, 0.612, 0.9); // blue
  g->move_to(0, 0);
  g->line_to(
      sin(hours + minutes / 12.0) * (_radius * 0.5),
     -cos(hours + minutes / 12.0) * (_radius * 0.5)
  );
  g->stroke();

  // draw the minutes hand
  g->set_line_width(_line_width / 2);
  g->set_source_rgba(0.666, 0.337, 0.612, 0.9); // blue
  g->move_to(0, 0);
  g->line_to(
      sin(minutes) * (_radius * 0.9),
      -cos(minutes) * (_radius * 0.9)
  );
  g->stroke();
  g->restore();

  return true;
}

bool Clock::on_timeout() {
  // force our program to redraw the entire clock
  auto win = get_window();
  if (win) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
  return true;
}
