#ifndef BACKTESTER_HPP
#define BACKTESTER_HPP

#include <common.hpp>
#include <event.hpp>

/* User headers */
#include <vector>

class Backtester;

struct Bucket {
  // Aggregator
};

class Backtester {
private:
  inline static uint64_t twindow_t_ns = 0;
  inline static uint32_t ewindow_events = 0;
  inline static uint32_t max_ewindow_vol = 0;

  double get_last_price(uint64_t t_ns);
  double get_max_price(uint64_t t_ns);
  double get_min_price(uint64_t t_ns);
  double get_vwap(uint64_t t_ns);
  double get_vwap_in_ewindow(uint64_t t_ns);

  Event prev_event{0, 0, 0, 0};

  long double spxv = 0;
  long double sv = 0;
  long double dspxv = 0;
  long double dsv = 0;
  std::vector<Event> w_events;
  void process_events(const Event &event);

public:
  enum class QueryType {
    QueryLastPrice,
    QueryMaxPrice,
    QueryMinPrice,
    QueryVWAP,
  };

  enum class WindowType {
    TimeWindow,
    EventWindow,
  };

  Backtester(uint64_t T, uint32_t K, uint32_t V) {
    Backtester::twindow_t_ns = T;
    Backtester::ewindow_events = K;
    Backtester::max_ewindow_vol = V;
  }
  void accept_event(Event event);
  double query(QueryType q_type, WindowType w_type, uint64_t timestamp);
};

using QueryType = Backtester::QueryType;
using WindowType = Backtester::WindowType;

#endif