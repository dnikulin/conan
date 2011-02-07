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

void ConanScreen::ruleAxes() {
    // Disable blending to over-draw lines
    glDisable(GL_BLEND);
    glBegin(GL_LINES);
    glLineWidth(1);

    // From origin
    glColor4f(1, 0, 0, 1);
    glVertex3i(0, 0, 0);
    glVertex3i(1, 0, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 1, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);

    // From far corner
    glColor4f(0, 0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 0, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 1, 0);

    glEnd();
}

void ConanScreen::rulePlanesBezel() {
    std::cerr << "ConanScreen::rulePlanesBezel()" << std::endl;

    // Disable blending to over-draw lines
    glDisable(GL_BLEND);

    // Viewport to full screen
    qreal width = screenSize.x();
    qreal height = screenSize.y();
    glViewport(0, 0, width, height);

    // First paint with thick black line
    glColor4f(0, 0, 0, 1);
    glLineWidth(3);
    rulePlanes();

    // Then paint with thin white line
    glColor4f(1, 1, 1, 1);
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
