#pragma once

#include <string>

std::string base64_decode(std::string const& encoded_string);
std::string base64_encode(std::string const& decoded_string);
