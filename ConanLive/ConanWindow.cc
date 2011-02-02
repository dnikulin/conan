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

#include "ConanWindow.hh"
#include "ui_ConanWindow.h"

#include <iostream>

ConanWindow::ConanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConanWindow)
{

    std::cerr << "ConanWindow::ConanWindow()" << std::endl;

    ui->setupUi(this);

    // Generate mock volume
    int const width = 8;
    volume.resize(width, width, width);
    volume = 0;

    for (int i = 0; i < width; i++)
        volume(i, i, i) = qreal(i + 1) / width;

    for (int i = 0; i < width; i++)
        volume(i, 2, 2) = qreal(i + 1) / width;

    // Connect screen to mock volume
    ui->screen->setVolume(&volume);
}

ConanWindow::~ConanWindow() {
    std::cerr << "ConanWindow::~ConanWindow()" << std::endl;

    delete ui;
}
