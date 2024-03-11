#include <gtest/gtest.h>
#include <signals_buffer.hpp>
#include <signals_consumer.hpp>

struct TestSignalsConsumer final : SignalsConsumer {
  void consume(const std::vector<Signal>& signals) override {
    ASSERT_EQ(_expected_signals.size(), signals.size());
    for (size_t i = 0; i < signals.size(); ++i) {
      ASSERT_EQ(_expected_signals.at(i).type, signals.at(i).type);
      ASSERT_EQ(_expected_signals.at(i).value, signals.at(i).value);
      ASSERT_EQ(_expected_signals.at(i).time, signals.at(i).time);
    }
  };

  static std::vector<Signal> _expected_signals;
};

std::vector<Signal> TestSignalsConsumer::_expected_signals;

TEST(SignalsBuffer, BasicFlow) {
  const std::vector<Signal> test_signals {
    {"key1", "val1", 111111},
    {"key2", "val2", 222222},
    {"key3", "val3", 333333}
  };
  // Double flush
  {
    SignalsBuffer processor(std::make_unique<TestSignalsConsumer>());
    TestSignalsConsumer::_expected_signals = test_signals;

    ASSERT_NO_THROW(processor.flush());
    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.flush());
  }
  // Empty vector
  {
    SignalsBuffer processor(std::make_unique<TestSignalsConsumer>());
    TestSignalsConsumer::_expected_signals = {};

    ASSERT_NO_THROW(processor.accumulate({}));
    ASSERT_NO_THROW(processor.flush());
  }
  // Double accumulate
  {
    SignalsBuffer processor(std::make_unique<TestSignalsConsumer>());
    auto expected_signals = test_signals;
    expected_signals.insert(expected_signals.end(), test_signals.begin(), test_signals.end());
    TestSignalsConsumer::_expected_signals = std::move(expected_signals);

    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.accumulate(test_signals));
    ASSERT_NO_THROW(processor.flush());
  }
  // Flush on destruction
  {
    auto processor = std::make_unique<SignalsBuffer>(std::make_unique<TestSignalsConsumer>());
    TestSignalsConsumer::_expected_signals = test_signals;

    ASSERT_NO_THROW(processor->accumulate(test_signals));
    processor = nullptr;
  }
}



