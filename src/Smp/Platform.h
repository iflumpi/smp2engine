//
// Title:
//      Platform.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines global includes, settings and macros for Smp.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PLATFORM_H
#define SMP_PLATFORM_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include <cassert>

#if defined(__linux__) || defined(__CYGWIN__) || defined(__QNX__)
#include <cctype>
#include <cstdint>
#include <sys/types.h>
#elif defined(__sgi)
#include <inttypes.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>

// ---------------------------------------------------------------------------
// --------------------------- Constant Declarations -------------------------
// ---------------------------------------------------------------------------

#ifdef WIN32
#ifndef NULL
#define NULL 0
#endif
#endif

// ---------------------------------------------------------------------------
// --------------------------- Platform Specific Types -----------------------
// ---------------------------------------------------------------------------

// Check __CYGWIN__ case before WIN32, because xercesc\util\AutoSense.hpp
// defines WIN32 in __CYGWIN__ case. Hence both, __CYGWIN__ and WIN32, are
// defined in the __CYGWIN__ case, if AutoSense.hpp is included.
#if defined(__linux__) || defined(__CYGWIN__) || defined(__QNX__)
typedef int64_t int64;   ///< 64 bit   signed integer type.
typedef uint64_t uint64; ///< 64 bit unsigned integer type.
#define PATH_SEPARATOR '/'

#ifndef INT64_MIN
#define INT64_MIN LLONG_MIN
#endif
#ifndef INT64_MAX
#define INT64_MAX LLONG_MAX
#endif

#elif defined(__sgi)
typedef int64_t int64;   ///< 64 bit   signed integer type.
typedef uint64_t uint64; ///< 64 bit unsigned integer type.
#define PATH_SEPARATOR '/'

#elif defined(WIN32)
typedef __int64 int64;           ///< 64 bit   signed integer type.
typedef unsigned __int64 uint64; ///< 64 bit unsigned integer type.

#ifndef INT64_MIN
#define INT64_MIN LLONG_MIN
#endif
#ifndef INT64_MAX
#define INT64_MAX LLONG_MAX
#endif

#define PATH_SEPARATOR '\\'
#endif

#endif // SMP_PLATFORM_H
