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

#include <iostream>

ConanScreen::ConanScreen(QWidget *parent) : QGLWidget(parent) {
    std::cerr << "ConanScreen::ConanScreen()" << std::endl;

    volume = NULL;
    volumeList = 0;
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

    // Assign orthographic projection matrix
    int voxels = volume->columns();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, voxels, 0, voxels, -voxels, voxels);

    // Assign model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -voxels);

    // Draw individual plane panes
    drawPlaneX();
    drawPlaneY();
    drawPlaneZ();
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

void ConanScreen::drawPlaneX() {
    std::cerr << "ConanScreen::drawPlaneX()" << std::endl;

    int voxels = volume->columns();
    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to bottom-right of screen
    glViewport(width / 2, 0, width / 2, height / 2);

    glPushMatrix();
    glTranslatef(0, voxels, voxels);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-voxels, -voxels, -voxels);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneY() {
    std::cerr << "ConanScreen::drawPlaneY()" << std::endl;

    int voxels = volume->columns();
    int width = screenSize.x();
    int height = screenSize.y();
    // Viewport to top-left of screen
    glViewport(0, height / 2, width / 2, height / 2);

    glPushMatrix();
    glTranslatef(voxels, 0, voxels);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-voxels, -voxels, -voxels);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneZ() {
    std::cerr << "ConanScreen::drawPlaneZ()" << std::endl;

    int width = screenSize.x();
    int height = screenSize.y();
    // Viewport to bottom-left of screen
    glViewport(0, 0, width / 2, height / 2);

    glPushMatrix();
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::rulePlanesBezel() {
    std::cerr << "ConanScreen::rulePlanesBezel()" << std::endl;

    // Reset viewport and model-view matrix
    qreal width = screenSize.x();
    qreal height = screenSize.y();
    glViewport(0, 0, width, height);
    glLoadIdentity();

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

    int voxels = volume->columns();
    glBegin(GL_LINES);

    // Vertical line
    glVertex2d(voxels / 2, 0);
    glVertex2d(voxels / 2, voxels);

    // Horizontal line
    glVertex2d(0,          voxels / 2);
    glVertex2d(voxels,     voxels / 2);

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

    int voxels = volume->columns();

    Conan::Volume const & vol = *volume;

    // Voxel scaling factor, to avoid saturation
    cl_float const factor = 2.f / voxels;

    for (int z = 0; z < voxels; z++) {
        for (int y = 0; y < voxels; y++) {
            for (int x = 0; x < voxels; x++) {
                cl_float const vox = vol(z, y, x);

                // Filter voxels by threshold
                if (vox < 0.001f)
                    continue;

                // Draw voxel cube
                // Voxel value becomes alpha
                glPushMatrix();
                glColor4f(1, 1, 1, vox * factor);
                glTranslated(0.5 + x, 0.5 + y, 0.5 + z);
                glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
}
