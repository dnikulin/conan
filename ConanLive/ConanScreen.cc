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

    drawPlanes = false;
    drawLogarithmic = false;
    drawQuadratic = false;
    drawWhite = false;

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

void ConanScreen::setDrawPlanes(bool drawPlanes) {
    this->drawPlanes = drawPlanes;
    repaint();
}

void ConanScreen::setDrawLogarithmic(bool drawLogarithmic) {
    this->drawLogarithmic = drawLogarithmic;
    makeTextures();
    repaint();
}

void ConanScreen::setDrawQuadratic(bool drawQuadratic) {
    this->drawQuadratic = drawQuadratic;
    makeTextures();
    repaint();
}

void ConanScreen::setDrawWhite(bool drawWhite) {
    this->drawWhite = drawWhite;
    repaint();
}

void ConanScreen::initializeGL() {
    // Configure additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH);

    applyBackColour();

    // Prepare existing volume if any
    makeTextures();
    makeGeometry();
}

void ConanScreen::paintGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    applyBackColour();

    if (volume == NULL)
        return;

    // Draw perspective pane
    setPerspective();
    drawSpin();

    // Draw individual plane panes
    if (drawPlanes) {
        setOrthographic();
        drawPlaneX();
        drawPlaneY();
        drawPlaneZ();

        // Rule lines between panes
        rulePlanesBezel();
    }

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

void ConanScreen::applyBackColour() {
    GLfloat v = (drawWhite ? 0 : 1);
    glClearColor(v, v, v, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ConanScreen::applyForeColour() {
    GLfloat v = (drawWhite ? 1 : 0);
    glColor4f(v, v, v, 1);
}
