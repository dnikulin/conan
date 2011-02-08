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
