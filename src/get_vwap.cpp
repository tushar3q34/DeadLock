#include <backtester.hpp>

// Returns VWAP for time window
double Backtester::get_vwap(uint64_t t_ns) {
  while (!w_events.empty() && (t_ns - w_events.back().t_ns > twindow_t_ns)) {
    w_events.pop_back();
  }
  double s_pxv = 0;
  double s_v = 0;
  for (size_t i = 0; i < w_events.size(); i++) {
    s_pxv += w_events[i].price * w_events[i].volume;
    s_v += w_events[i].volume;
  }
  if (s_v == 0) {
    return NotANumber;
  }
  return s_pxv / s_v;
}

// Returns VWAP for event window
double Backtester::get_vwap_in_ewindow(uint64_t t_ns) {
  while (!w_events.empty() && (t_ns - w_events.back().t_ns > twindow_t_ns)) {
    w_events.pop_back();
  }
  double s_pxv = 0;
  double s_v = 0;
  for (size_t i = 0;
       i < std::min(w_events.size(), (size_t)Backtester::ewindow_events); i++) {
    s_pxv += w_events[i].price * w_events[i].volume;
    s_v += w_events[i].volume;
  }
  if (s_v == 0) {
    return NotANumber;
  }
  return s_pxv / s_v;
}