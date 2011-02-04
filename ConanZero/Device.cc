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

#include "Device.hh"

#include <iostream>

namespace Conan {

Device::Device(QObject * parent, cl::Device const & device) :
    QObject(parent),
    m_device(device)
{

    std::cerr << "Device::Device()" << std::endl;

    m_platform = device.getInfo<CL_DEVICE_PLATFORM>();
    m_devices.push_back(m_device);
    m_context = cl::Context(m_devices);
    m_queue = cl::CommandQueue(m_context, m_device);
}

Device::~Device() {
    std::cerr << "Device::~Device()" << std::endl;
}

static void reportBuild(cl::Device &device, cl::Program &program) {
    std::string log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
    if (log.empty() == false) {
        std::string devname = device.getInfo<CL_DEVICE_NAME>();
        std::cerr << "--------------------------------" << std::endl;
        std::cerr << "Compile log for " << devname << std::endl << std::endl;
        std::cerr << log << std::endl;
        std::cerr << "--------------------------------" << std::endl;
        std::cerr.flush();
    }
}

cl::Program Device::compile(QString const & source) {
    cl::Program::Sources clsource(1, std::make_pair(source.toAscii(), source.size()));
    cl::Program program = cl::Program(m_context, clsource);

    try {
        program.build(m_devices);
        reportBuild(m_device, program);
        return program;
    } catch (cl::Error err) {
        std::cerr << err.what() << " (code " << err.err() << ")" << std::endl;
        std::cerr.flush();
        reportBuild(m_device, program);
        throw err;
    }
}

void Device::findDevices(QObject * parent, Devices & devices) {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    for (size_t np = 0; np < platforms.size(); np++) {
        std::vector<cl::Device> ndevices;
        platforms.at(np).getDevices(CL_DEVICE_TYPE_ALL, &ndevices);

        for (size_t nd = 0; nd < ndevices.size(); nd++) {
            Device *device = new Device(parent, ndevices.at(nd));
            devices.append(device);
        }
    }
}

}
