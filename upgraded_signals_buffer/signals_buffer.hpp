#pragma once

#include "types.hpp"
#include "signals_consumer.hpp"

#include <memory>

struct SignalsBuffer {
  SignalsBuffer(std::unique_ptr<SignalsConsumer> consumer)
  : _consumer(std::move(consumer)) {}

  void accumulate(const std::vector<Signal>& signals) {
    _signals.reserve(_signals.size() + signals.size());
    _signals.insert(_signals.end(), signals.begin(), signals.end());
  }

  void flush() {
    if (_signals.empty()) {
      return;
    }

    if (_consumer) {
      _consumer->consume(_signals);
    }
//  send_signals(_signals); // SEND SIGNALS VIA NETWORK
    _signals.clear();
  }

private:
  std::vector<Signal> _signals;
  std::unique_ptr<SignalsConsumer> _consumer;
};