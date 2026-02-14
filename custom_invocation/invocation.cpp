#include <backtester.hpp>
#include <cassert>
#include <iomanip>
#include <iostream>

/*
Input Format:

- The first line contains three space-separated integers: T K V.
- The second line contains a single integer N, representing the number of lines
that follow.
- Each of the next N lines are one of the following:
  1) Event:
      E <idx> <timestamp> <price> <volume>
      Example:
        E 3 300 10.5 30
  2) Query:
      Q <QueryType> <WindowType> <timestamp>
      where:
        QueryType  ∈ {MIN, MAX, LAST, VWAP}
        WindowType ∈ {E, T}
      Example:
        Q VWAP E 400
*/

int main() {
  // and you thought there's no cp just because it's a dev contest :D
#ifndef ONLINE_JUDGE
  freopen("custom_invocation/input.txt", "r", stdin);
  freopen("custom_invocation/output.txt", "w", stdout);
#else
#endif
  uint64_t T;
  uint32_t K, V;
  std::cin >> T >> K >> V;

  Backtester *b = new Backtester(T, K, V);

  std::cout << std::fixed << std::setprecision(6);

  uint32_t numLines;
  std::cin >> numLines;
  int e_no = 1;

  for (uint32_t i = 0; i < numLines; i++) {
    std::string lineType;
    std::cin >> lineType;

    if (lineType == "E") {
      uint32_t idx, v;
      uint64_t t;
      double p;
      std::cin >> idx >> t >> p >> v;

      if (idx != e_no++) {
        assert(false && "Event index must be increasing");
      }

      b->accept_event(Event{idx, t, p, v});

    } else if (lineType == "Q") {
      std::string q_type, w_type;
      uint64_t t_ns;
      std::cin >> q_type >> w_type >> t_ns;

      if (q_type == "LAST" && w_type == "T") {
        std::cout << "L = "
                  << b->query(QueryType::QueryLastPrice, WindowType::TimeWindow,
                              t_ns)
                  << std::endl;
      } else if (q_type == "MAX" && w_type == "E") {
        std::cout << "M = "
                  << b->query(QueryType::QueryMaxPrice, WindowType::EventWindow,
                              t_ns)
                  << std::endl;
      } else if (q_type == "MIN" && w_type == "E") {
        std::cout << "m = "
                  << b->query(QueryType::QueryMinPrice, WindowType::EventWindow,
                              t_ns)
                  << std::endl;
      } else if (q_type == "VWAP") {
        if (w_type == "E") {
          std::cout << "V = "
                    << b->query(QueryType::QueryVWAP, WindowType::EventWindow,
                                t_ns)
                    << std::endl;
        } else if (w_type == "T") {
          std::cout << "v = "
                    << b->query(QueryType::QueryVWAP, WindowType::TimeWindow,
                                t_ns)
                    << std::endl;
        } else {
          assert(false && "Invalid window type");
        }
      } else {
        assert(false && "Invalid query");
      }
    } else {
      assert(false && "Invalid line type");
    }
  }
}
