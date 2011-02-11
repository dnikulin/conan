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

#include "ColourMap.hh"

namespace Conan {

static cl_uchar4 const hotRGB[] = {
    {{0x00, 0x00, 0x00, 0x00}},
    {{0xFF, 0x00, 0x00, 0x20}},
    {{0xFF, 0x8C, 0x00, 0x40}},
    {{0xFF, 0xFF, 0x00, 0x80}},
    {{0xFF, 0xFF, 0xFF, 0xA0}}
};

static size_t const hotCount = sizeof(hotRGB) / sizeof(hotRGB[0]);
static size_t const hotLast = hotCount - 1;

cl_uchar4 colourHot(cl_float const part) {
    assert (part >= 0);
    assert (part <= 1);

    cl_float const index = part * (hotCount - 1);
    assert (index >= 0);
    assert (index <  hotCount);

    size_t const i1 = size_t(index);

    if (i1 == hotLast)
        return hotRGB[hotLast];

    size_t const i2 = i1 + 1;
    assert (i1 < hotCount);
    assert (i2 < hotCount);

    cl_float const factor = index - float(i1);
    assert (factor >= 0);
    assert (factor <= 1);

    cl_uchar4 const rgb1 = hotRGB[i1];
    cl_uchar4 const rgb2 = hotRGB[i2];

    cl_uchar4 out;
    for (size_t i = 0; i < 4; i++) {
        cl_float const c1 = cl_float(rgb1.s[i]) * (1.f - factor);
        cl_float const c2 = cl_float(rgb2.s[i]) * factor;
        out.s[i] = cl_uchar(c1 + c2);
    }

    return out;
}

}
