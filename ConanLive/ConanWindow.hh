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

#ifndef CONAN_LIVE_WINDOW_HH
#define CONAN_LIVE_WINDOW_HH

#include "SharedVolume.hh"
#include "FileWorker.hh"

#include <QMainWindow>
#include <QThread>

namespace Ui {
    class ConanWindow;
}

class ConanWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit ConanWindow(QWidget *parent = 0);
    ~ConanWindow();

    void makeStartingVolume();
    void loadPlugins();
    void loadPlugin(QObject * object);

signals:

    void changedVolume(Conan::SharedVolume volume);
    void selectedTextFile(QString path);

public slots:

    void clickedOpenTextFile();
    void volumeRead(QString path, Conan::SharedVolume volume);

public: // Leave public to allow access for plugins

    Ui::ConanWindow *ui;

    QThread fileThread;
    Conan::FileWorker fileWorker;
};

#endif // CONAN_LIVE_WINDOW_HH
