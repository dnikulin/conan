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
