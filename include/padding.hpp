#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <gmpxx.h>

std::vector<uint8_t> to_bytes(const mpz_class& x, size_t len);
std::vector<uint8_t> strip_pkcs1_v15(const std::vector<uint8_t>& em);
std::string to_hex(const std::vector<uint8_t>& bytes);