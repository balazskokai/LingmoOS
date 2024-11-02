/*
 * Compilation Copyright (c) 1995-2019 by Wei Dai.  All rights reserved.
 *	This copyright applies only to this software distribution package
 *	as a compilation, and does not imply a copyright on any particular
 *	file in the package.
 * 
 *	Boost Software License - Version 1.0 - August 17th, 2003
 *
 *	Permission is hereby granted, free of charge, to any person or organization
 *	obtaining a copy of the software and accompanying documentation covered by
 *	this license (the "Software") to use, reproduce, display, distribute,
 *	execute, and transmit the Software, and to prepare derivative works of the
 *	Software, and to permit third-parties to whom the Software is furnished to
 *	do so, all subject to the following:
 * 
 *	The copyright notices in the Software and this entire statement, including
 *	the above license grant, this restriction and the following disclaimer,
 *	must be included in all copies of the Software, in whole or in part, and
 *	all derivative works of the Software, unless such copies or derivative
 *	works are solely in the form of machine-executable object code generated by
 *	a source language processor.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 *	SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 *	FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 *	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *	DEALINGS IN THE SOFTWARE.
 */

// trap.h - written and placed in public domain by Jeffrey Walton.

/// \file trap.h
/// \brief Debugging and diagnostic assertions
/// \details <tt>CRYPTOPP_ASSERT</tt> is the library's debugging and diagnostic
///   assertion. <tt>CRYPTOPP_ASSERT</tt> is enabled by <tt>CRYPTOPP_DEBUG</tt>,
///   <tt>DEBUG</tt> or <tt>_DEBUG</tt>.
/// \details <tt>CRYPTOPP_ASSERT</tt> raises a <tt>SIGTRAP</tt> (Unix) or calls
///   <tt>__debugbreak()</tt> (Windows). <tt>CRYPTOPP_ASSERT</tt> is only in
///   effect when the user requests a debug configuration. Unlike Posix assert,
///   <tt>NDEBUG</tt> (or failure to define it) does not affect the library.
///   The traditional Posix define <tt>NDEBUG</tt> has no effect on
///   <tt>CRYPTOPP_DEBUG</tt> or DebugTrapHandler.
/// \since Crypto++ 5.6.5
/// \sa DebugTrapHandler, <A
///   HREF="http://github.com/weidai11/cryptopp/issues/277">Issue 277</A>,
///   <A HREF="http://seclists.org/oss-sec/2016/q3/520">CVE-2016-7420</A>

#ifndef CRYPTOPP_TRAP_H
#define CRYPTOPP_TRAP_H

#include "config.h"

#if defined(CRYPTOPP_DEBUG)
#  include <iostream>
#  include <sstream>
#  if defined(UNIX_SIGNALS_AVAILABLE)
#    include "ossig.h"
#  elif defined(CRYPTOPP_WIN32_AVAILABLE) && !defined(__CYGWIN__)
     extern "C" __declspec(dllimport) void __stdcall DebugBreak();
     extern "C" __declspec(dllimport)  int __stdcall IsDebuggerPresent();
#  endif
#endif // CRYPTOPP_DEBUG

// ************** run-time assertion ***************

#if defined(CRYPTOPP_DOXYGEN_PROCESSING)
/// \brief Debugging and diagnostic assertion
/// \details <tt>CRYPTOPP_ASSERT</tt> is the library's debugging and diagnostic
///   assertion. <tt>CRYPTOPP_ASSERT</tt> is enabled by the preprocessor macros
///   <tt>CRYPTOPP_DEBUG</tt>, <tt>DEBUG</tt> or <tt>_DEBUG</tt>.
/// \details <tt>CRYPTOPP_ASSERT</tt> raises a <tt>SIGTRAP</tt> (Unix) or calls
///   <tt>DebugBreak()</tt> (Windows). <tt>CRYPTOPP_ASSERT</tt> is only in effect
///   when the user explicitly requests a debug configuration.
/// \details If you want to ensure <tt>CRYPTOPP_ASSERT</tt> is inert, then <em>do
///   not</em> define <tt>CRYPTOPP_DEBUG</tt>, <tt>DEBUG</tt> or <tt>_DEBUG</tt>.
///   Avoiding the defines means <tt>CRYPTOPP_ASSERT</tt> is preprocessed into an
///   empty string.
/// \details The traditional Posix define <tt>NDEBUG</tt> has no effect on
///   <tt>CRYPTOPP_DEBUG</tt>, <tt>CRYPTOPP_ASSERT</tt> or DebugTrapHandler.
/// \details An example of using CRYPTOPP_ASSERT and DebugTrapHandler is shown
///   below. The library's test program, <tt>cryptest.exe</tt> (from test.cpp),
///   exercises the structure:
///  <pre>
///    \#if defined(CRYPTOPP_DEBUG) && defined(UNIX_SIGNALS_AVAILABLE)
///    static const DebugTrapHandler g_dummyHandler;
///    \#endif
///
///    int main(int argc, char* argv[])
///    {
///       CRYPTOPP_ASSERT(argv != nullptr);
///       ...
///    }
///  </pre>
/// \since Crypto++ 5.6.5
/// \sa DebugTrapHandler, SignalHandler, <A
///   HREF="http://github.com/weidai11/cryptopp/issues/277">Issue 277</A>,
///   <A HREF="http://seclists.org/oss-sec/2016/q3/520">CVE-2016-7420</A>
#  define CRYPTOPP_ASSERT(exp) { ... }
#endif

#if defined(CRYPTOPP_DEBUG) && defined(UNIX_SIGNALS_AVAILABLE)
#  define CRYPTOPP_ASSERT(exp) {                                  \
    if (!(exp)) {                                                 \
      std::ostringstream oss;                                     \
      oss << "Assertion failed: " << __FILE__ << "("              \
          << __LINE__ << "): " << __func__                        \
          << std::endl;                                           \
      std::cerr << oss.str();                                     \
      raise(SIGTRAP);                                             \
    }                                                             \
  }
#elif CRYPTOPP_DEBUG && defined(CRYPTOPP_WIN32_AVAILABLE) && !defined(__CYGWIN__)
#  define CRYPTOPP_ASSERT(exp) {                                  \
    if (!(exp)) {                                                 \
      std::ostringstream oss;                                     \
      oss << "Assertion failed: " << __FILE__ << "("              \
          << __LINE__ << "): " << __FUNCTION__                    \
          << std::endl;                                           \
      std::cerr << oss.str();                                     \
      if (IsDebuggerPresent()) {DebugBreak();}                    \
    }                                                             \
  }
#endif // DEBUG and Unix or Windows

// Remove CRYPTOPP_ASSERT in non-debug builds.
//  Can't use CRYPTOPP_UNUSED due to circular dependency
#ifndef CRYPTOPP_ASSERT
#  define CRYPTOPP_ASSERT(exp) (void)0
#endif

NAMESPACE_BEGIN(CryptoPP)

// ************** SIGTRAP handler ***************

#if (CRYPTOPP_DEBUG && defined(UNIX_SIGNALS_AVAILABLE)) || defined(CRYPTOPP_DOXYGEN_PROCESSING)
/// \brief Default SIGTRAP handler
/// \details DebugTrapHandler() can be used by a program to install an empty
///   SIGTRAP handler. If present, the handler ensures there is a signal
///   handler in place for <tt>SIGTRAP</tt> raised by
///   <tt>CRYPTOPP_ASSERT</tt>. If <tt>CRYPTOPP_ASSERT</tt> raises
///   <tt>SIGTRAP</tt> <em>without</em> a handler, then one of two things can
///   occur. First, the OS might allow the program to continue. Second, the OS
///   might terminate the program. OS X allows the program to continue, while
///   some Linuxes terminate the program.
/// \details If DebugTrapHandler detects another handler in place, then it will
///   not install a handler. This ensures a debugger can gain control of the
///   <tt>SIGTRAP</tt> signal without contention. It also allows multiple
///   DebugTrapHandler to be created without contentious or unusual behavior.
///   Though multiple DebugTrapHandler can be created, a program should only
///   create one, if needed.
/// \details A DebugTrapHandler is subject to C++ static initialization
///   [dis]order. If you need to install a handler and it must be installed
///   early, then reference the code associated with
///   <tt>CRYPTOPP_INIT_PRIORITY</tt> in cryptlib.cpp and cpu.cpp.
/// \details If you want to ensure <tt>CRYPTOPP_ASSERT</tt> is inert, then
///   <em>do not</em> define <tt>CRYPTOPP_DEBUG</tt>, <tt>DEBUG</tt> or
///   <tt>_DEBUG</tt>. Avoiding the defines means <tt>CRYPTOPP_ASSERT</tt>
///   is processed into <tt>((void)(exp))</tt>.
/// \details The traditional Posix define <tt>NDEBUG</tt> has no effect on
///   <tt>CRYPTOPP_DEBUG</tt>, <tt>CRYPTOPP_ASSERT</tt> or DebugTrapHandler.
/// \details An example of using \ref CRYPTOPP_ASSERT "CRYPTOPP_ASSERT" and
///   DebugTrapHandler is shown below. The library's test program,
///   <tt>cryptest.exe</tt> (from test.cpp), exercises the structure:
///  <pre>
///    \#if defined(CRYPTOPP_DEBUG) && defined(UNIX_SIGNALS_AVAILABLE)
///    static const DebugTrapHandler g_dummyHandler;
///    \#endif
///
///    int main(int argc, char* argv[])
///    {
///       CRYPTOPP_ASSERT(argv != nullptr);
///       ...
///    }
///  </pre>
/// \since Crypto++ 5.6.5
/// \sa \ref CRYPTOPP_ASSERT "CRYPTOPP_ASSERT", SignalHandler, <A
///   HREF="http://github.com/weidai11/cryptopp/issues/277">Issue 277</A>,
///   <A HREF="http://seclists.org/oss-sec/2016/q3/520">CVE-2016-7420</A>

#if defined(CRYPTOPP_DOXYGEN_PROCESSING)
class DebugTrapHandler : public SignalHandler<SIGILL, false> { };
#else
typedef SignalHandler<SIGILL, false> DebugTrapHandler;
#endif

#endif  // Linux, Unix and Documentation

NAMESPACE_END

#endif // CRYPTOPP_TRAP_H