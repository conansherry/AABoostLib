#ifndef COMMON_H
#define COMMON_H

#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
	#include <iostream>
#endif

#include <vector>
#include <stdint.h>

using namespace std;

#define UINT uint32_t
#define INT int32_t

typedef UINT CLASSIFIER;

#endif