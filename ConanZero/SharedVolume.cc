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

#include "SharedVolume.hh"

#include <QSharedData>

namespace Conan {

class SharedVolumeData : public QSharedData, public boost::noncopyable {
public:

    explicit SharedVolumeData() {}

    explicit SharedVolumeData(int width) : array(width, width, width) {
        array = 0;
    }

    ~SharedVolumeData() {
        array.free();
    }

    Volume array;
    QReadWriteLock lock;
};

SharedVolume::SharedVolume() : data(new SharedVolumeData()) {
}

SharedVolume::SharedVolume(int width) : data(new SharedVolumeData(width)) {
}

SharedVolume::SharedVolume(SharedVolume const &that) : data(that.data) {
}

SharedVolume & SharedVolume::operator =(SharedVolume const &that) {
    data.reset();
    data = that.data;
    return *this;
}

SharedVolume::~SharedVolume() {
    data.reset();
}

Volume & SharedVolume::array() {
    return data->array;
}

Volume const & SharedVolume::array() const {
    return data->array;
}

QReadWriteLock *SharedVolume::lock() {
    return &data->lock;
}

}
