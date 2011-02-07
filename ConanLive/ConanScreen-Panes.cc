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
    int width = screenSize.x();
    int height = screenSize.y();
    // Viewport to bottom-left of screen
    glViewport(0, 0, width / 2, height / 2);

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
    glCallList(volumeList);
}
