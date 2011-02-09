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
#include "Math.hh"

void ConanScreen::makeGeometry() {
    if (volume == NULL)
        return;

    // Number of voxels along each axis
    GLuint const voxels = volume->columns();

    // Allocate list if unavailable
    if (volumeList == 0)
        volumeList = glGenLists(1);

    // Start compiling display list
    glNewList(volumeList, GL_COMPILE);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH);

    // Scale to normalised coordinates
    GLfloat const scale = 1.0f / voxels;
    glPushMatrix();
    glScalef(scale, scale, scale);

    // Bind full 3D texture before pushing quads
    glBindTexture(GL_TEXTURE_3D, volumeTexture);

    glBegin(GL_QUADS);

    // Create one quad per slice per plane
    for (GLuint nplane = 0; nplane < 3; nplane++) {
        for (GLuint nslice = 0; nslice < voxels; nslice++) {
            // Create default spans for all dimensions
            GLfloat min[] = {     0,      0,      0};
            GLfloat max[] = {voxels, voxels, voxels};

            // Replace min and max along a specific dimension
            min[nplane] = max[nplane] = (0.5f + nslice);

            // Normalise to texture coordinate
            GLfloat const fslice = min[nplane] / voxels;

            switch (nplane) {
            case 0:
                // X plane, Y and Z change
                glTexCoord3f(fslice, 0, 0);
                glVertex3f(min[0], min[1], min[2]);
                glTexCoord3f(fslice, 0, 1);
                glVertex3f(min[0], min[1], max[2]);
                glTexCoord3f(fslice, 1, 1);
                glVertex3f(min[0], max[1], max[2]);
                glTexCoord3f(fslice, 1, 0);
                glVertex3f(min[0], max[1], min[2]);
                break;

            case 1:
                // Y plane, X and Z change
                glTexCoord3f(0, fslice, 0);
                glVertex3f(min[0], min[1], min[2]);
                glTexCoord3f(0, fslice, 1);
                glVertex3f(min[0], min[1], max[2]);
                glTexCoord3f(1, fslice, 1);
                glVertex3f(max[0], min[1], max[2]);
                glTexCoord3f(1, fslice, 0);
                glVertex3f(max[0], min[1], min[2]);
                break;

            case 2:
                // Z plane, X and Y change
                glTexCoord3f(0, 0, fslice);
                glVertex3f(min[0], min[1], min[2]);
                glTexCoord3f(0, 1, fslice);
                glVertex3f(min[0], max[1], min[2]);
                glTexCoord3f(1, 1, fslice);
                glVertex3f(max[0], max[1], min[2]);
                glTexCoord3f(1, 0, fslice);
                glVertex3f(max[0], min[1], min[2]);
                break;
            }
        }
    }

    // Finish compiling display list
    glEnd();
    glPopMatrix();
    glEndList();
}

void ConanScreen::makeTextures() {
    if (volume == NULL)
        return;

    // Blitz Range for all of an axis
    blitz::Range all = blitz::Range::all();

    GLuint const voxels = volume->columns();

    Conan::Volume vol(voxels, voxels, voxels);
    vol = *volume;
    vol.transposeSelf(2, 1, 0);
    Conan::normalise(vol);

    if (drawLogarithmic) {
        vol *= 1e9;
        vol += 1;
        vol = blitz::log(vol);
        Conan::normalise(vol);
    }

    if (drawQuadratic) {
        vol = (vol * vol);
        Conan::normalise(vol);
    }

    vol *= (2.0f / voxels);

    if (volumeTexture == 0)
        glGenTextures(1, &volumeTexture);

    // Select texture
    glBindTexture(GL_TEXTURE_3D, volumeTexture);

    // Replace alpha channel entirely, don't modulate
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Set mipmap and filtering modes
    // May still be overridden before rendering occurs
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Assign texture data
    glTexImage3D(GL_TEXTURE_3D, 0, GL_ALPHA,
                 voxels, voxels, voxels, 0,
                 GL_ALPHA, GL_FLOAT, vol.data());
}
