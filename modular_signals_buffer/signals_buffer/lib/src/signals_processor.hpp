#pragma once

#include "types.hpp"
#include "signals_consumer.hpp"

#include <memory>

struct SignalsBuffer {
  SignalsBuffer(std::unique_ptr<SignalsConsumer> consumer);
  ~SignalsBuffer();

  void accumulate(const std::vector<Signal>& signals);
  void flush();

private:
  std::vector<Signal> _signals;
  std::unique_ptr<SignalsConsumer> _consumer;
};