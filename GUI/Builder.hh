#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newBox();
    void newTriangle();
    void newSimulatedScene();
    void newVirtualScene();
    void loadSettings();
    void activaColorShading();
    void activaNormalShader();
    void activaNColorShader();
    void activaBlinn_Phong();
    void activaCel_Shading();
    void showBoundingVolumes(bool show);
signals:
     void settingsChanged();
};

