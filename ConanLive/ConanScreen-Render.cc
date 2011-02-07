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
    glColor4f(1, 1, 1, 1);

    // Scale to normalised coordinates
    GLfloat const scale = 1.0f / voxels;
    glPushMatrix();
    glScalef(scale, scale, scale);

    glBegin(GL_QUADS);

    // Create one quad per slice per plane
    for (GLuint nplane = 0, index = 0; nplane < 3; nplane++) {
        for (GLuint nslice = 0; nslice < voxels; nslice++, index++) {
            // Create default spans for all dimensions
            GLint min[] = {     0,      0,      0};
            GLint max[] = {voxels, voxels, voxels};

            // Bind texture before pushing quad
            glBindTexture(GL_TEXTURE_2D, textureList.at(index));

            // Draw each quad twice, to close each cube
            for (size_t offset = 0; offset <= 1; offset++) {
                // Replace min and max along a specific dimension
                min[nplane] = max[nplane] = nslice + offset;

                // Push quad with winding order pointing away from origin
                glTexCoord2i(0, 0);
                glVertex3i(min[0], min[1], min[2]);

                switch (nplane) {
                case 0:
                    // X plane, Y and Z change
                    glTexCoord2i(0, 1);
                    glVertex3i(min[0], min[1], max[2]);
                    glTexCoord2i(1, 1);
                    glVertex3i(min[0], max[1], max[2]);
                    glTexCoord2i(1, 0);
                    glVertex3i(min[0], max[1], min[2]);
                    break;

                case 1:
                    // Y plane, X and Z change
                    glTexCoord2i(0, 1);
                    glVertex3i(min[0], min[1], max[2]);
                    glTexCoord2i(1, 1);
                    glVertex3i(max[0], min[1], max[2]);
                    glTexCoord2i(1, 0);
                    glVertex3i(max[0], min[1], min[2]);
                    break;

                case 2:
                    // Z plane, X and Y change
                    glTexCoord2i(0, 1);
                    glVertex3i(min[0], max[1], min[2]);
                    glTexCoord2i(1, 1);
                    glVertex3i(max[0], max[1], min[2]);
                    glTexCoord2i(1, 0);
                    glVertex3i(max[0], min[1], min[2]);
                    break;
                }
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

    Conan::Volume const & vol = *volume;
    GLuint const voxels = vol.columns();
    GLuint const nslices = voxels * 3;
    cl_float const factor = 2.0f / voxels;

    // Free existing textures
    if (textureList.isEmpty() == false) {
        glDeleteTextures(textureList.size(), textureList.data());
        textureList.clear();
    }

    // Allocate textures
    textureList.resize(nslices);
    glGenTextures(nslices, textureList.data());

    // Blitz Range for all of an axis
    blitz::Range all = blitz::Range::all();

    // Create one texture per slice per plane
    for (GLuint nplane = 0, index = 0; nplane < 3; nplane++) {
        for (GLuint nslice = 0; nslice < voxels; nslice++, index++) {
            Conan::Slice slice(voxels, voxels);

            switch(nplane) {
            case 0: slice = vol(nslice, all, all).transpose(1, 0); break;
            case 1: slice = vol(all, nslice, all).transpose(1, 0); break;
            case 2: slice = vol(all, all, nslice).transpose(1, 0); break;
            }

            slice *= factor;

            // Select texture
            glBindTexture(GL_TEXTURE_2D, textureList.at(index));

            // Replace alpha channel entirely, don't modulate
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

            // Set mipmap and filtering modes
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            // Assign texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA,
                         voxels, voxels, 0,
                         GL_ALPHA, GL_FLOAT, slice.data());
        }
    }
}
