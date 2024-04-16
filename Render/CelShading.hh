#pragma once

#include "ShadingStrategy.hh"

class CelShading: public ShadingStrategy
{
public:
    CelShading() {};
    virtual vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight);
    ~CelShading(){};
};