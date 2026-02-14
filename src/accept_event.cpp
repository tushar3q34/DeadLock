#include <backtester.hpp>

void Backtester::accept_event(Event event) {
  prev_event = event;
  process_events(event);
}

void Backtester::process_events(const Event &event) {
  w_events.insert(w_events.begin(), event);
  uint64_t t_curr = event.t_ns;
  while (w_events.size() != 0 &&
         (t_curr - w_events.back().t_ns) > Backtester::twindow_t_ns) {
    w_events.pop_back();
  }
}