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

#include "TextFile.hh"

#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

ConanWindow::ConanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConanWindow)
{

    std::cerr << "ConanWindow::ConanWindow()" << std::endl;

    ui->setupUi(this);

    // Connect signal for volume change
    ui->screen->connect(this,
        SIGNAL(changedVolume(Conan::Volume const *)),
        SLOT(setVolume(Conan::Volume const *))
    );

    // Generate mock volume
    int const width = 8;
    volume.resize(width, width, width);
    volume = 0;

    for (int i = 0; i < width; i++)
        volume(i, i, i) = qreal(i + 1) / width;

    for (int i = 0; i < width; i++)
        volume(i, 2, 2) = qreal(i + 1) / width;

    // Signal volume change now
    emit changedVolume(&volume);
}

ConanWindow::~ConanWindow() {
    std::cerr << "ConanWindow::~ConanWindow()" << std::endl;

    delete ui;
}

void ConanWindow::clickedOpenTextFile() {
    std::cerr << "ConanWindow::clickedOpenTextFile()" << std::endl;

    QString path = QFileDialog::getOpenFileName(this,
            "Open text data file", "", "*.txt");

    if (path.isEmpty())
        return;

    Conan::readTextFileVolume(&volume, path);

    // Check the volume was actually populated
    if (volume.columns() < 1) {
        QString message("Volume size must be a cube of a power of 2");
        QMessageBox::critical(this, message, message);
    }

    // Either way, emit signal for volume change
    emit changedVolume(&volume);
}
