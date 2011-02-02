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

#ifndef CONANSCREEN_HH
#define CONANSCREEN_HH

#include <QGLWidget>

class ConanScreen : public QGLWidget
{
    Q_OBJECT

public:

    explicit ConanScreen(QWidget *parent = 0);
    virtual ~ConanScreen();

signals:

public slots:

protected:

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void drawPlaneX();
    virtual void drawPlaneY();
    virtual void drawPlaneZ();

    qreal aspect;
};

#endif // CONANSCREEN_HH
