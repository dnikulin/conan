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

void ConanScreen::setOrthographic() {
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
    // Assign perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, getAspect(), 0, 4);

    // Assign model-view matrix
    // Looks at center of volume from a distance
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.5, 0.5, 2.0,
              0.5, 0.5, 0.5,
              0.0, 1.0, 0.0);

    // Apply mouse-controlled rotation
    applyRotation();
}

void ConanScreen::drawPlaneX() {
    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to bottom-right of screen
    glViewport(width / 2, 0, width / 2, height / 2);
    applyForeColour();

    glPushMatrix();
    glTranslatef(0, 1, 1);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1, -1, -1);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneY() {
    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to top-left of screen
    glViewport(0, height / 2, width / 2, height / 2);
    applyForeColour();

    glPushMatrix();
    glTranslatef(1, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-1, -1, -1);
    glCallList(volumeList);
    glPopMatrix();
}

void ConanScreen::drawPlaneZ() {
    int width = screenSize.x();
    int height = screenSize.y();

    // Viewport to bottom-left of screen
    glViewport(0, 0, width / 2, height / 2);
    applyForeColour();

    glCallList(volumeList);
}

void ConanScreen::drawSpin() {
    int width = screenSize.x();
    int height = screenSize.y();

    if (drawPlanes) {
        // Viewport to top-right of screen
        glViewport(width / 2, height / 2, width / 2, height / 2);
    }

    ruleAxes();

    applyForeColour();
    glCallList(volumeList);
}
