#include <backtester.hpp>

// Returns max price for Event Window
double Backtester::get_max_price(uint64_t t_ns) {
  if (w_events.empty()) {
    return NotANumber;
  }
  double max_price = w_events[0].price;
  for (size_t i = 0;
       i < std::min(w_events.size(), (size_t)Backtester::ewindow_events); i++) {
    max_price = std::max(w_events[i].price, max_price);
  }
  return max_price;
}

// Returns min price for Event Window
double Backtester::get_min_price(uint64_t t_ns) {
  if (w_events.empty()) {
    return NotANumber;
  }
  double min_price = w_events[0].price;
  for (size_t i = 0;
       i < std::min(w_events.size(), (size_t)Backtester::ewindow_events); i++) {
    min_price = std::min(w_events[i].price, min_price);
  }
  return min_price;
}