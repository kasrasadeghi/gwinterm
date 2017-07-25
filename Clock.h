#ifndef KTERM_CLOCK_H
#define KTERM_CLOCK_H

#include <gtkmm/drawingarea.h>

class Clock : public Gtk::DrawingArea {
public:
  Clock();
  virtual ~Clock();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  bool on_timeout();

  double _radius;
  double _line_width;
};


#endif //KTERM_CLOCK_H
