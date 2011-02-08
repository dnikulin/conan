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

#ifndef CONAN_LIVE_WINDOW_HH
#define CONAN_LIVE_WINDOW_HH

#include "ConanTypes.hh"

#include <QMainWindow>

namespace Ui {
    class ConanWindow;
}

class ConanWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit ConanWindow(QWidget *parent = 0);
    ~ConanWindow();

signals:

    void changedVolume(Conan::Volume const * volume);

public slots:

    void clickedOpenTextFile();

private:

    Ui::ConanWindow *ui;

    // Current volume
    // TODO: Factor out into session state
    Conan::Volume volume;
};

#endif // CONAN_LIVE_WINDOW_HH
