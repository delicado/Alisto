#ifndef CONFIG_H
#define CONFIG_H
#include <cstdint>

#include "fixed_point.h"

using Float = TFixedPoint<uint32_t, 16>;

using Char = char;

static constexpr size_t cfg_static_param_size = 32;

#endif // CONFIG_H
