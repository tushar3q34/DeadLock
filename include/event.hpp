#ifndef EVENT_HPP
#define EVENT_HPP

#include <common.hpp>

struct Event {
  uint32_t idx;
  uint64_t t_ns;
  double price;
  uint32_t volume;
  Event(uint32_t idx, uint64_t t, double p, uint32_t v)
      : idx(idx), t_ns(t), price(p), volume(v) {}
};

#endif