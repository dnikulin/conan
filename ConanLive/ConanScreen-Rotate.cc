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

#include <QMouseEvent>

#include <GL/glut.h>

#include <iostream>

static qreal anorm(qreal iangle) {
    qreal angle = iangle;
    while (angle <   0) angle += 360;
    while (angle > 360) angle -= 360;
    return angle;
}

static qreal d2r(qreal deg) {
    return (M_PI * deg) / 180;
}

void ConanScreen::mousePressEvent(QMouseEvent *event) {
    std::cerr << "ConanScreen::mousePressEvent()" << std::endl;

    mousePoint = event->pos();
}

void ConanScreen::mouseMoveEvent(QMouseEvent *event) {
    std::cerr << "ConanScreen::mouseMoveEvent()" << std::endl;

    if (event->buttons() & Qt::LeftButton) {
        // Window dimensions
        qreal const nx = screenSize.x();
        qreal const ny = screenSize.y();

        // Raw pixel delta
        qreal const px = event->x() - mousePoint.x();
        qreal const py = event->y() - mousePoint.y();

        // Normalised to angle
        qreal const ax = (px * 360) / nx;
        qreal const ay = (py * 360) / ny;

        // Adjust and re-normalise angles
        rotation.x = anorm(rotation.x + ax);
        rotation.y = anorm(rotation.y + ay);
    }

    mousePoint = event->pos();
    repaint();
}

void ConanScreen::applyRotation() {
    std::cerr << "ConanScreen::applyRotation()" << std::endl;

    // Move model back to world origin
    glTranslatef(+0.5f, +0.5f, +0.5f);

    // Rotate around exact Y axis, using horizontal angle
    glRotatef(rotation.x, 0, 1, 0);

    // Adjust X axis based on horizontal angle
    qreal const xr = d2r(rotation.x);
    qreal const ax = ::cos(xr);
    qreal const az = ::sin(xr);

    // Rotate around adjusted X axis, using vertical angle
    glRotatef(rotation.y, ax, 0, az);

    // Movel model back to volume centre
    glTranslatef(-0.5f, -0.5f, -0.5f);
}
