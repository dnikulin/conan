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

#ifndef CONAN_FILE_TEXT_FILE_HH
#define CONAN_FILE_TEXT_FILE_HH

#include "ConanFileGlobal.hh"
#include "Volume.hh"

namespace Conan {

void CONANFILESHARED_EXPORT readTextFileVolume(
    Volume *volume,
    QString const &path
);

}

#endif // CONAN_FILE_TEXT_FILE_HH
