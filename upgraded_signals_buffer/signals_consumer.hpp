#pragma once

#include "types.hpp"

#include <vector>

struct SignalsConsumer {
  virtual ~SignalsConsumer() = default;

  virtual void consume(const std::vector<Signal>& signals) = 0;
};

struct NetworkSignalsConsumer final : SignalsConsumer {
  void consume(const std::vector<Signal>& signals) override {
    //  send_signals(signals); // SEND SIGNALS VIA NETWORK
  }
};
