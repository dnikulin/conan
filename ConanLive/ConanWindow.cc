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

#include "ConanWindow.hh"
#include "ui_ConanWindow.h"

#include "ConanLivePlugin.hh"
#include "TextFile.hh"

#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>

ConanWindow::ConanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConanWindow)
{

    ui->setupUi(this);

    // Create file worker assigned to thread
    fileThread.setObjectName("fileThread");
    fileWorker.setObjectName("fileWorker");
    fileWorker.moveToThread(&fileThread);

    // Connect signal for volume change by window
    ui->screen->connect(this,
        SIGNAL(changedVolume(Conan::SharedVolume)),
        SLOT(setVolume(Conan::SharedVolume))
    );

    // Connect signals for volume read from file
    fileWorker.connect(this,
        SIGNAL(selectedTextFile(QString)),
        SLOT(readTextFile(QString))
    );

    connect(&fileWorker,
        SIGNAL(volumeRead(QString, Conan::SharedVolume)),
        SLOT(volumeRead(QString, Conan::SharedVolume))
    );

    fileThread.start();
    loadPlugins();
    makeStartingVolume();
}

ConanWindow::~ConanWindow() {
    delete ui;
}

void ConanWindow::makeStartingVolume() {
    // Create shared data array
    Conan::SharedVolume volume(8);
    Conan::Volume &vol(volume.array());

    blitz::Range all = blitz::Range::all();

    // Distinguish each axis
    vol(all, 0, 0) = 100;
    vol(1, all, 1) = 200;
    vol(2, 2, all) = 300;

    // Signal volume change
    emit changedVolume(volume);
}

void ConanWindow::loadPlugins() {
    // Start from binary directory
    QDir root(qApp->applicationDirPath());

    // Move down to Plugins directory
    root.cd("Plugins");

    foreach (QString name, root.entryList(QDir::Files)) {
        QString path(root.absoluteFilePath(name));
        QPluginLoader loader(path);
        QObject *object = loader.instance();
        if (object != NULL)
            loadPlugin(object);
    }
}

void ConanWindow::loadPlugin(QObject *object) {
    ConanLivePlugin * plugin = qobject_cast<ConanLivePlugin *>(object);
    if (plugin != NULL)
        plugin->installPlugin(this);
}

void ConanWindow::clickedOpenTextFile() {
    QString path = QFileDialog::getOpenFileName(this,
            "Open text data file", "", "*.txt");

    if (path.isEmpty())
        return;

    emit selectedTextFile(path);
}

void ConanWindow::volumeRead(QString path, Conan::SharedVolume volume) {
    // Check the volume was actually populated
    if (volume.width() < 1) {
        QString message("Volume size must be a cube of a power of 2");
        QMessageBox::critical(this, path, message);
        return;
    }

    emit changedVolume(volume);
}
