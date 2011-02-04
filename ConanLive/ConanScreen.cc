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

#include <GL/glut.h>

#include <cmath>
#include <iostream>

ConanScreen::ConanScreen(QWidget *parent) : QGLWidget(parent) {
    std::cerr << "ConanScreen::ConanScreen()" << std::endl;

    volume = NULL;
    volumeList = 0;

    rotation.x = rotation.y = 0;
}

ConanScreen::~ConanScreen() {
    std::cerr << "ConanScreen::~ConanScreen()" << std::endl;
}

void ConanScreen::setVolume(Conan::Volume const * volume) {
    std::cerr << "ConanScreen::setVolume()" << std::endl;

    this->volume = volume;

    prepareList();
    repaint();
}

void ConanScreen::initializeGL() {
    std::cerr << "ConanScreen::initializeGL()" << std::endl;

    // Configure additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare existing volume if any
    prepareList();
}

void ConanScreen::paintGL() {
    std::cerr << "ConanScreen::paintGL()" << std::endl;

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
    std::cerr << "ConanScreen::resizeGL("
            << width << ", " << height << ")" << std::endl;

    screenSize.setX(width);
    screenSize.setY(height);

    // Viewport to entire screen
    glViewport(0, 0, width, height);
}

void ConanScreen::setOrthographic() {
    std::cerr << "ConanScreen::setOrthographic()" << std::endl;

    // Assign orthographic projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -2, 2);

    // Assign model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -1);
}

void ConanScreen::setPerspective() {
    std::cerr << "ConanScreen::setPerspective()" << std::endl;

    // Assign perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, getAspect(), 0, 4);

    // Assign model-view matrix
    // Looks at center of volume from a distance
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.5, 0.5, 1.5,
              0.5, 0.5, 0.5,
              0.0, 1.0, 0.0);

    // Apply mouse-controlled rotation
    applyRotation();
}

void ConanScreen::drawPlaneX() {
    std::cerr << "ConanScreen::drawPlaneX()" << std::endl;

    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to bottom-right of screen
    glViewport(width / 2, 0, width / 2, height / 2);

    glPushMatrix();
    glTranslatef(0, 1, 1);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1, -1, -1);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneY() {
    std::cerr << "ConanScreen::drawPlaneY()" << std::endl;

    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to top-left of screen
    glViewport(0, height / 2, width / 2, height / 2);

    glPushMatrix();
    glTranslatef(1, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-1, -1, -1);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneZ() {
    std::cerr << "ConanScreen::drawPlaneZ()" << std::endl;

    int width = screenSize.x();
    int height = screenSize.y();
    // Viewport to bottom-left of screen
    glViewport(0, 0, width / 2, height / 2);

    glCallList(volumeList);
}

void ConanScreen::drawSpin() {
    std::cerr << "ConanScreen::drawSpin()" << std::endl;

    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to top-right of screen
    glViewport(width / 2, height / 2, width / 2, height / 2);

    glCallList(volumeList);
}

void ConanScreen::rulePlanesBezel() {
    std::cerr << "ConanScreen::rulePlanesBezel()" << std::endl;

    // Viewport to full screen
    qreal width = screenSize.x();
    qreal height = screenSize.y();
    glViewport(0, 0, width, height);

    // First paint with thick black line
    glColor3f(0, 0, 0);
    glLineWidth(3);
    rulePlanes();

    // Then paint with thin white line
    glColor3f(1, 1, 1);
    glLineWidth(1);
    rulePlanes();
}

void ConanScreen::rulePlanes() {
    std::cerr << "ConanScreen::rulePlanes()" << std::endl;

    glBegin(GL_LINES);

    // Vertical line
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.5f, 1.0f);

    // Horizontal line
    glVertex2f(0.0f, 0.5f);
    glVertex2f(1.0f, 0.5f);

    glEnd();
}

void ConanScreen::prepareList() {
    std::cerr << "ConanScreen::prepareList()" << std::endl;

    // Allocate list if unavailable
    if (volumeList == 0)
        volumeList = glGenLists(1);

    glNewList(volumeList, GL_COMPILE);
    drawVoxels();
    glEndList();
}

void ConanScreen::drawVoxels() {
    std::cerr << "ConanScreen::drawVoxels()" << std::endl;

    if (volume == NULL)
        return;

    // Number of voxels along each axis
    int const voxels = volume->columns();

    // Reciprocal of voxels, for scaling coordinates
    GLfloat const scale = 1.0f / voxels;

    // Voxel value factor, to avoid alpha saturation
    cl_float const factor = 2.0f / voxels;

    // Raw volume data in flat memory
    cl_float const * const data = volume->data();

    for (int z = 0, i = 0; z < voxels; z++) {
        GLfloat const zf = (0.5f + z) / voxels;

        for (int y = 0; y < voxels; y++) {
            GLfloat const yf = (0.5f + y) / voxels;

            for (int x = 0; x < voxels; x++, i++) {
                GLfloat const xf = (0.5f + x) / voxels;
                cl_float const vox = data[i];

                // Filter voxels by threshold
                if (vox < 0.001f)
                    continue;

                // Draw voxel cube
                // Voxel value becomes alpha
                glPushMatrix();
                glColor4f(1, 1, 1, vox * factor);
                glTranslatef(xf, yf, zf);
                glutSolidCube(scale);
                glPopMatrix();
            }
        }
    }
}

qreal ConanScreen::getAspect() const {
    qreal const width = screenSize.x();
    qreal const height = screenSize.y();
    if (height < 1)
        return 1;

    return width / height;
}
