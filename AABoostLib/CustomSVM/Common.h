#ifndef COMMON_H
#define COMMON_H

#ifdef WIN32
	#pragma warning(disable:4251)
#endif

#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
	#include <iostream>
	#include <iomanip>
#endif

#include <vector>
#include <stdint.h>

#include <time.h>

using namespace std;

#ifdef WIN32
	#define EXPORT_CLASS_EXPORTS

	#ifdef EXPORT_CLASS_EXPORTS

		#define EXPORT_CLASS __declspec(dllexport)

	#else

		#define EXPORT_CLASS __declspec(dllimport)

	#endif
#else
	#define EXPORT_CLASS
#endif

#endif