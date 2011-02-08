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
    glBegin(GL_LINES);

    // Vertical line
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.5f, 1.0f);

    // Horizontal line
    glVertex2f(0.0f, 0.5f);
    glVertex2f(1.0f, 0.5f);

    glEnd();
}
