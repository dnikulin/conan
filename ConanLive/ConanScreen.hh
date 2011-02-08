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
    QVector<GLuint> textureList;
};

#endif // CONAN_LIVE_SCREEN_HH
