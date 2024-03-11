#include "signals_buffer.hpp"

SignalsBuffer::SignalsBuffer(std::unique_ptr<SignalsConsumer> consumer)
: _consumer(std::move(consumer))
{}

SignalsBuffer::~SignalsBuffer() {
  try {
    flush();
  } catch (std::exception&) {
    // LOG ERROR
  } catch (...) {
    // LOG ERROR
  }
}

void SignalsBuffer::accumulate(const std::vector<Signal>& signals) {
  _signals.reserve(_signals.size() + signals.size());
  _signals.insert(_signals.end(), signals.begin(), signals.end());
}

void SignalsBuffer::flush() {
  if (_signals.empty()) {
    return;
  }

  if (_consumer) {
    _consumer->consume(_signals);
  }
//  send_signals(_signals); // SEND SIGNALS VIA NETWORK
  _signals.clear();
}