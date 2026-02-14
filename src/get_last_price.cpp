#include <backtester.hpp>

// Returns last price for Time Window
double Backtester::get_last_price(uint64_t t_ns){
    if(t_ns - prev_event.t_ns > twindow_t_ns){
        return NotANumber;
    }else if(prev_event.volume == 0){
        return NotANumber;
    }
    return prev_event.price;
}