#include <backtester.hpp>

double Backtester::query(QueryType q_type, WindowType w_type,
                         uint64_t timestamp) {
  if (q_type == QueryType::QueryLastPrice) {
    return get_last_price(timestamp);
  } else if (q_type == QueryType::QueryMaxPrice) {
    return get_max_price(timestamp);
  } else if (q_type == QueryType::QueryMinPrice) {
    return get_min_price(timestamp);
  } else if (w_type == WindowType::TimeWindow) {
    return get_vwap(timestamp);
  } else if (w_type == WindowType::EventWindow) {
    return get_vwap_in_ewindow(timestamp);
  }
  return NotANumber;
}