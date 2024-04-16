#include "NColorShading.hh"


vec3 NColorShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) 
{
    if (infos.empty()) return vec3(0.0, 0.0, 0.0);
    
    vec3 factor = infos[0]->mat->kt;
    vec3 color = infos[0]->mat->Kd * (vec3(1.0, 1.0, 1.0) - infos[0]->mat->kt);
    for (int i = 1; i < (int) infos.size(); i++) 
    {
        color += (vec3(1.0, 1.0, 1.0) - infos[i]->mat->kt) * factor * infos[i]->mat->Kd;
        factor *= infos[i]->mat->kt;
    }
    return color;
}