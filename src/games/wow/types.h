/*
 * types.h
 *
 *  Created on: 7 Aug. 2015
 *      Author: Jeromnimo
 */

#ifndef _TYPES_H_
#define _TYPES_H_

// STL headers
#ifdef min
  #undef min
#endif

#ifdef max
  #undef max
#endif

#if defined(_WINDOWS)
  #include <windows.h>
	typedef unsigned char uint8;
	typedef char int8;
	typedef unsigned __int16 uint16;
	typedef __int16 int16;
	typedef unsigned __int32 uint32;
	typedef __int32 int32;
	#if !defined(uint64)
		typedef unsigned __int64 uint64;
	#endif
	#if !defined(int64)
		typedef __int64 int64;
	#endif
	#if !defined(ssize_t) && defined(Q_OS_WIN64)
		typedef __int64 ssize_t;
	#elif !defined(ssize_t)
		typedef __int32 ssize_t;
	#endif
#else
	#include <stdint.h>
	typedef uint8_t uint8;
	typedef int8_t int8;
	typedef uint16_t uint16;
	typedef int16_t int16;
	typedef uint32_t uint32;
	typedef int32_t int32;
	typedef uint64_t uint64;
	typedef int64_t int64;
#endif

#endif /* _TYPES_H_ */