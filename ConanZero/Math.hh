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

#ifndef CONAN_ZERO_MATH_HH
#define CONAN_ZERO_MATH_HH

#include "ConanZeroGlobal.hh"

namespace Conan {

template<class DT, int rank>
void normalise(blitz::Array<DT, rank> &array) {
    DT max = blitz::max(array);
    DT min = blitz::min(array);
    array *= (DT(1) / (max - min));
}

}

#endif // CONAN_ZERO_MATH_HH
