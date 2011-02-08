// Copyright (c) 2011  Dmitri Nikulin
//
// This file is part of Conan.
//
// Conan is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// Conan is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Conan.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CONAN_ZERO_GLOBAL_HH
#define CONAN_ZERO_GLOBAL_HH

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
