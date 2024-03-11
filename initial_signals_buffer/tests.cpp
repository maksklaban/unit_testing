#include <gtest/gtest.h>

#include "signals_buffer.hpp"

TEST(SignalsBuffer, BasicFlow) {
  const std::vector<Signal> test_signals {
    {"key1", "val1", 111111},
    {"key2", "val2", 222222},
    {"key3", "val3", 333333}
  };
  {
    SignalsBuffer processor;
    ASSERT_NO_THROW(processor.flush());
    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.flush());
  }
  {
    SignalsBuffer processor;
    ASSERT_NO_THROW(processor.accumulate({}));
    ASSERT_NO_THROW(processor.flush());
  }
  {
    SignalsBuffer processor;
    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.flush());
  }
}

