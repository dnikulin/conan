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

#include "TextFile.hh"

#include <QFile>
#include <QTextStream>

namespace Conan {

static int edgeSize(size_t totalSize) {
    // Start with edge length 1
    size_t edge = 1;

    while (true) {
        // Calculate cube of edge
        size_t const cube = edge * edge * edge;

        // If total size was missed, the total size
        // is not a cube of a power of two
        if (cube > totalSize)
            return 0;

        if (cube < totalSize) {
            // Haven't reached the size yet,
            // try again with doubled edge
            edge <<= 1;
            continue;
        }

        // Must be an exact match, return it
        return int(edge);
    }
}

void readTextFileVolume(Volume *volume, QString const &path) {
    // Free existing volume
    volume->free();

    // Consume file as a flat array
    std::vector<cl_float> buffer;
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);

            while (true) {
                cl_float value = 0;
                stream >> value;

                // Test for end before saving value
                if (stream.atEnd())
                    break;

                buffer.push_back(value);
            }
        }
    }

    // Calculate edge length, if valid
    int const edge = edgeSize(buffer.size());

    // For invalid size, return without filling the volume
    if (edge < 1)
        return;

    // Resize the volume to a cube of the edge size
    volume->resize(edge, edge, edge);

    // Populate the volume
    cl_float * const data = volume->data();
    for (unsigned int i = 0; i < buffer.size(); i++)
        data[i] = buffer.at(i);
}

}
