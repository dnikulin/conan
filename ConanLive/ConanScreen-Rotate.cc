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

#include <QMouseEvent>

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
    mousePoint = event->pos();
}

void ConanScreen::mouseMoveEvent(QMouseEvent *event) {
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
    // Move model back to world origin
    glTranslatef(+0.5f, +0.5f, +0.5f);

    // Rotate around exact Y axis, using horizontal angle
    glRotatef(rotation.x, 0, 1, 0);

    // Adjust X axis based on horizontal angle
    qreal const xr = d2r(rotation.x);
    qreal const ax = std::cos(xr);
    qreal const az = std::sin(xr);

    // Rotate around adjusted X axis, using vertical angle
    glRotatef(rotation.y, ax, 0, az);

    // Movel model back to volume centre
    glTranslatef(-0.5f, -0.5f, -0.5f);
}
