#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.hh"
#include "PointLight.hh"

#include "glm/gtx/norm.hpp"

class AreaLight: public Light {
public:
    AreaLight() {};
    /*
     * Constructor de la classe AreaLight.
     * param p1: bottom left corner de la llum.
     * param p2: top right corner de la llum.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param a: coeficient a de l'atenuacio.
     * param b: coeficient b de l'atenuacio.
     * param c: coeficient c de l'atenuacio.
     * */
    AreaLight(vec3 center, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c);
    AreaLight(vec3 p1, vec3 p2, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c);
    virtual ~AreaLight() {}
    vec3 getP1();
    vec3 getP2();
    vec3 getCenter();
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vector<PointLight> getPointLights();
private:
    vec3 p1; // bottom left corner
    vec3 p2; // top right corner
    vec3 center; // center of the area light
    float a; // atenuacio: terme constant
    float b; // atenuacio: terme lineal
    float c; // atenuacio: terme quadratic
    vector<PointLight> pointLights;
    void createPointLights();
};

#endif // AREALIGHT_H
