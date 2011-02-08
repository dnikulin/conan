// Copyright (c) 2011 Dmitri Nikulin. All rights reserved.
//
// This file is part of Conan.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY DMITRI NIKULIN "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL DMITRI NIKULIN OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CONAN_ZERO_GLOBAL_HH
#define CONAN_ZERO_GLOBAL_HH

// Include standard headers before blitz,
// as they're not transitive on mingw.
#include <cmath>
#include <cstdlib>

// Use QtCore types.
#include <QtCore/QObject>

// Use official OpenCL C++ wrapper with exceptions enabled.
// When QtOpenCL is officially released, Conan will
// very likely switch to use it.
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

// Use Blitz C++ for numeric arrays.
#include <blitz/array.h>

// Use misc Boost headers.
#include <boost/noncopyable.hpp>

// Declare macro for symbol import/export.
#if defined(CONANZERO_LIBRARY)
#  define CONANZEROSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONANZEROSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONAN_ZERO_GLOBAL_HH
