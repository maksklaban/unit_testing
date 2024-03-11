#include <gtest/gtest.h>

#include "base64_functions.hpp"

TEST(Base64, BasicFlow) {
  const std::string s = "René Nyffenegger\nhttp://www.renenyffenegger.ch\npassion for data\n";

  std::string encoded = base64_encode(s);
  std::string decoded = base64_decode(encoded);

  EXPECT_EQ(s, decoded);

  // Test all possibilites of fill bytes (none, one =, two ==)
  // References calculated with: https://www.base64encode.org/

  std::string rest0_original = "abc";
  std::string rest0_reference = "YWJj";

  std::string rest0_encoded = base64_encode(rest0_original);
  std::string rest0_decoded = base64_decode(rest0_encoded);

  EXPECT_EQ(rest0_reference, rest0_encoded);
  EXPECT_EQ(rest0_original, rest0_decoded);

  std::string rest1_original = "abcd";
  std::string rest1_reference = "YWJjZA==";

  std::string rest1_encoded = base64_encode(rest1_original);
  std::string rest1_decoded = base64_decode(rest1_encoded);

  EXPECT_EQ(rest1_reference, rest1_encoded);
  EXPECT_EQ(rest1_original, rest1_decoded);

  std::string rest2_original = "abcde";
  std::string rest2_reference = "YWJjZGU=";

  std::string rest2_encoded = base64_encode(rest2_original);
  std::string rest2_decoded = base64_decode(rest2_encoded);

  EXPECT_EQ(rest2_reference, rest2_encoded);
  EXPECT_EQ(rest2_original, rest2_decoded);
}
