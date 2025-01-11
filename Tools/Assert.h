#pragma once

#include <stdio.h>

#define NH_BREAK() std::abort()
#define NH_LOG(...) fprintf(stderr, __VA_ARGS__)
#define NH_ASSERT(_b, ...) { if (!(_b)) { NH_LOG(__VA_ARGS__); NH_BREAK(); } }