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

#include "ConanMock.hh"
#include "MockDialog.hh"

#include <QApplication>
#include <QMenuBar>

#include <iostream>

Q_EXPORT_PLUGIN2(conan_mock_plugin, ConanMock);

ConanMock::ConanMock() {
    window = NULL;
}

ConanMock::~ConanMock() {
}

void ConanMock::installPlugin(ConanWindow * window) {
    std::cerr << "ConanMock::installPlugin()" << std::endl;

    this->window = window;

    QMenuBar *menuBar = window->menuBar();

    QMenu *menu = new QMenu(menuBar);
    menu->setObjectName(QString::fromUtf8("menu_Mock"));
    menu->setTitle(QApplication::translate("ConanMock", "&Mock", 0, QApplication::UnicodeUTF8));

    QAction *actionGenerate = new QAction(window);
    actionGenerate->setObjectName(QString::fromUtf8("actionGenerate"));
    actionGenerate->setText(QApplication::translate("ConanMock", "&Generate volume...", 0, QApplication::UnicodeUTF8));

    QObject::connect(actionGenerate, SIGNAL(activated()),
                     this, SLOT(clickedGenerateData()));

    menu->addAction(actionGenerate);
    menuBar->addMenu(menu);
}

void ConanMock::clickedGenerateData() {
    if (window == NULL)
        return;

    MockDialog *dialog = new MockDialog(window);
    dialog->setVisible(true);
}
