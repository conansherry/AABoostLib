#ifndef COMMON_H
#define COMMON_H

#pragma warning(disable:4251)

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

#define EXPORT_CLASS_EXPORTS

#ifdef EXPORT_CLASS_EXPORTS

	#define EXPORT_CLASS __declspec(dllexport)

#else

	#define EXPORT_CLASS __declspec(dllimport)

#endif

#define NUMLENGTH 10

#endif