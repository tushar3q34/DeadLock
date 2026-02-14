# IP configuration
IP := <fill_here>
CXX = g++

# DO NOT CHANGE BELOW THIS

PROJECT_NAME := DeadLock
CXXFLAGS = -std=c++17 -I include -pthread

INVOC_SRCS = custom_invocation/invocation.cpp src/query.cpp src/get_vwap.cpp src/accept_event.cpp src/get_last_price.cpp src/get_max_min.cpp
INVOC_TARGET = custom_invocation/backtester_invoc

invoc_all: $(INVOC_TARGET)

$(INVOC_TARGET): $(INVOC_SRCS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

invoc_run: $(INVOC_TARGET)
	@./$(INVOC_TARGET)

clean:
	@rm -f $(PUBLIC_TARGET) $(INVOC_TARGET)

invoc_check: invoc_all invoc_run clean
 
submit:
	echo "Submitting $(PROJECT_NAME) to $(IP):8585..."
	cd .. && tar -cf - $(PROJECT_NAME) | nc $(IP) 8585