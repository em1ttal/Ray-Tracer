#ifndef NORMALSHADING_HH
#define NORMALSHADING_HH

#include "ShadingStrategy.hh"

class NormalShading: public ShadingStrategy
{
    public:
        NormalShading() {};
        vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) override;
        ~NormalShading(){};
};

#endif // NORMALSHADING_HH
