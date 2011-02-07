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

#include "ConanScreen.hh"

ConanScreen::ConanScreen(QWidget *parent) : QGLWidget(parent) {
    volume = NULL;
    volumeList = 0;

    rotation.x = rotation.y = 0;
}

ConanScreen::~ConanScreen() {
}

void ConanScreen::setVolume(Conan::Volume const * volume) {
    this->volume = volume;

    makeTextures();
    makeGeometry();
    repaint();
}

void ConanScreen::initializeGL() {
    // Configure additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare existing volume if any
    makeTextures();
    makeGeometry();
}

void ConanScreen::paintGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (volume == NULL)
        return;

    // Draw perspective pane
    setPerspective();
    drawSpin();

    // Draw individual plane panes
    setOrthographic();
    drawPlaneX();
    drawPlaneY();
    drawPlaneZ();

    // Rule lines between panes
    rulePlanesBezel();

    glFlush();
}

void ConanScreen::resizeGL(int width, int height) {
    screenSize.setX(width);
    screenSize.setY(height);

    // Viewport to entire screen
    glViewport(0, 0, width, height);
}

qreal ConanScreen::getAspect() const {
    qreal const width = screenSize.x();
    qreal const height = screenSize.y();
    if (height < 1)
        return 1;

    return width / height;
}
