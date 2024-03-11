#include <string>
#include <vector>

struct Signal {
  std::string type;
  std::string value;
  int64_t time;
};

struct SignalsBuffer {
  void accumulate(const std::vector<Signal>& signals) {
    _signals.reserve(_signals.size() + signals.size());
    _signals.insert(_signals.end(), signals.begin(), signals.end());
  }

  void flush() {
    if (_signals.empty()) {
      return;
    }

//  send_signals(_signals); // SEND SIGNALS VIA NETWORK
    _signals.clear();
  }


private:
  std::vector<Signal> _signals;
};