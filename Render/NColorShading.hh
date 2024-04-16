#ifndef NCOLORSHADING_HH
#define NCOLORSHADING_HH

#include "ShadingStrategy.hh"

class NColorShading: public ShadingStrategy
{
    public:
        NColorShading() {};
        vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) override;
        ~NColorShading(){};
};

#endif // NCOLORSHADING_HH