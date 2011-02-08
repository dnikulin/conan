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

#ifndef CONAN_LIVE_SCREEN_HH
#define CONAN_LIVE_SCREEN_HH

#include "Volume.hh"

#include <QGLWidget>

class ConanScreen : public QGLWidget {
    Q_OBJECT

public:

    explicit ConanScreen(QWidget *parent = 0);
    virtual ~ConanScreen();

signals:

public slots:

    void setVolume(Conan::Volume const * volume);
    void setDrawPlanes(bool drawPlanes);
    void setDrawLogarithmic(bool drawLogarithmic);
    void setDrawQuadratic(bool drawQuadratic);
    void setDrawWhite(bool drawWhite);

protected:

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void setOrthographic();
    virtual void setPerspective();
    virtual void applyBackColour();
    virtual void applyForeColour();

    virtual void drawPlaneX();
    virtual void drawPlaneY();
    virtual void drawPlaneZ();
    virtual void drawSpin();
    virtual void ruleAxes();

    virtual void rulePlanesBezel();
    virtual void rulePlanes();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void applyRotation();

    qreal getAspect() const;

    virtual void makeGeometry();
    virtual void makeTextures();

    Conan::Volume const * volume;
    bool drawPlanes;
    bool drawLogarithmic;
    bool drawQuadratic;
    bool drawWhite;

    QPoint screenSize;
    QPoint mousePoint;

    cl_float2 rotation;

    GLuint volumeList;
    GLuint volumeTexture;
};

#endif // CONAN_LIVE_SCREEN_HH
