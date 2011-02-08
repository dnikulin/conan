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

#ifndef CONAN_ZERO_DEVICE_HH
#define CONAN_ZERO_DEVICE_HH

#include "ConanZeroGlobal.hh"

#include <QtCore/QString>
#include <QtCore/QVector>

namespace Conan {

class Device;
typedef QVector<Device *> Devices;

class Device : public QObject, public boost::noncopyable {
    Q_OBJECT

public:

    static void findDevices(QObject * parent, Devices & devices);

    Device(QObject * parent, cl::Device const & device);
    virtual ~Device();

    virtual cl::Program compile(QString const & source);

protected:

    cl::Platform               m_platform;
    cl::Device                 m_device;
    std::vector<cl::Device>    m_devices;
    cl::Context                m_context;
    cl::CommandQueue           m_queue;
};

}

#endif // CONAN_ZERO_DEVICE_HH
