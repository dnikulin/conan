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
