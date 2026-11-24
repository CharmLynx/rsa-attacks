#pragma once

#include <gmpxx.h>
#include "io.hpp"

mpz_class hastad_attack(const BroadcastData& data, unsigned long e);