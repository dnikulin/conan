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

#include "ConanScreen.hh"

ConanScreen::ConanScreen(QWidget *parent) : QGLWidget(parent) {
    volumeList = 0;
    volumeTexture = 0;

    drawPlanes = false;
    drawLogarithmic = false;
    drawQuadratic = false;
    drawWhite = false;

    rotation.x = rotation.y = 0;
}

ConanScreen::~ConanScreen() {
}

void ConanScreen::setVolume(Conan::SharedVolume nvolume) {
    // Obtain read lock while generating texture
    {
        QReadLocker lock(nvolume.lock());
        int const width = nvolume.width();
        if (volume.columns() != width)
            volume.resize(width, width, width);
        volume = nvolume.array();
        makeTextures();
    }

    // Geometry is independent of array data
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

void ConanScreen::setDrawInterpolated(bool drawInterpolated) {
    this->drawInterpolated = drawInterpolated;
    repaint();
}

void ConanScreen::initializeGL() {
    // Configure additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_3D);
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

    if (volumeTexture == 0)
        return;

    // Apply any texture settings
    applyTextureSettings();

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

void ConanScreen::applyTextureSettings() {
    glBindTexture(GL_TEXTURE_3D, volumeTexture);

    GLint filter = drawInterpolated ? GL_LINEAR : GL_NEAREST;
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, filter);
}
