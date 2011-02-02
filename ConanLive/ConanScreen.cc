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

#include <iostream>

ConanScreen::ConanScreen(QWidget *parent) : QGLWidget(parent) {
    std::cerr << "ConanScreen::ConanScreen()" << std::endl;
}

ConanScreen::~ConanScreen() {
    std::cerr << "ConanScreen::~ConanScreen()" << std::endl;
}

void ConanScreen::initializeGL() {
    std::cerr << "ConanScreen::initializeGL()" << std::endl;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ConanScreen::paintGL() {
    std::cerr << "ConanScreen::paintGL()" << std::endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
}

void ConanScreen::resizeGL(int width, int height) {
    std::cerr << "ConanScreen::resizeGL("
            << width << ", " << height << ")" << std::endl;

    glViewport(0, 0, width, height);
    aspect = qreal(width ? width : 1) / qreal(height ? height : 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void ConanScreen::drawPlaneX() {
    std::cerr << "ConanScreen::drawPlaneX()" << std::endl;
}

void ConanScreen::drawPlaneY() {
    std::cerr << "ConanScreen::drawPlaneY()" << std::endl;
}

void ConanScreen::drawPlaneZ() {
    std::cerr << "ConanScreen::drawPlaneZ()" << std::endl;
}

