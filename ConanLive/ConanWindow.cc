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

    // Connect signal for volume change
    ui->screen->connect(this,
        SIGNAL(changedVolume(Conan::Volume const *)),
        SLOT(setVolume(Conan::Volume const *))
    );

    // Load plugins now
    loadPlugins();

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
    delete ui;
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

    Conan::readTextFileVolume(&volume, path);

    // Check the volume was actually populated
    if (volume.columns() < 1) {
        QString message("Volume size must be a cube of a power of 2");
        QMessageBox::critical(this, message, message);
    }

    // Either way, emit signal for volume change
    emit changedVolume(&volume);
}
