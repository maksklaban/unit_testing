#include "base64_functions.hpp"

#include <array>

namespace {

  const std::string base64_chars =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz"
          "0123456789+/";


  bool is_base64(unsigned char c) {
    return ((isalnum(c) != 0) || (c == '+') || (c == '/'));
  }

} // anonymous

std::string base64_decode(std::string const& encoded_string) {
  int in_len = static_cast<int>(encoded_string.size());
  int i = 0;
  int j = 0;
  int in_ = 0;
  std::array<unsigned char, 4> char_array_4{};
  std::array<unsigned char, 3> char_array_3{};
  std::string ret;

  while (((in_len--) != 0) && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4.at(i++) = encoded_string[in_];
    in_++;

    if (i ==4) {
      for (i = 0; i < 4; i++) {
        char_array_4.at(i) = static_cast<unsigned char>(base64_chars.find(char_array_4.at(i)));
      }

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; i < 3; i++) {
        ret += char_array_3.at(i);
      }
      i = 0;
    }
  }

  if (i != 0) {
    for (j = i; j < 4; j++) {
      char_array_4.at(j) = 0;
    }

    for (j = 0; j < 4; j++) {
      char_array_4.at(j) = static_cast<unsigned char>(base64_chars.find(char_array_4.at(j)));
    }

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) {
      ret += char_array_3.at(j);
    }
  }

  return ret;
}

std::string base64_encode(std::string const& decoded_string) {
  auto bytes_to_encode = reinterpret_cast<const unsigned char*>(decoded_string.c_str());
  auto in_len = static_cast<unsigned int>(decoded_string.size());
  std::string ret;
  int i = 0;
  int j = 0;
  std::array<unsigned char, 3> char_array_3{};
  std::array<unsigned char, 4> char_array_4{};

  while ((in_len--) != 0u) {
    char_array_3.at(i++) = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++) {
        ret += base64_chars[char_array_4.at(i)];
      }
      i = 0;
    }
  }

  if (i != 0)
  {
    for(j = i; j < 3; j++) {
      char_array_3.at(j) = '\0';
    }

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++) {
      ret += base64_chars[char_array_4.at(j)];
    }

    while((i++ < 3)) {
      ret += '=';
    }

  }

  return ret;

}
