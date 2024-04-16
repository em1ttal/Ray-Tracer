#include "CelShading.hh"

vec3 CelShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight)
{
    if (info.empty()) return vec3(0, 0, 0);
    
    vec3 color = vec3(0, 0, 0);
    if (shadow) 
    {
        float s = 1;
        for (auto light: lights){
            s *= computeShadow(scene, light, info[0]->p);
            color += light->getIa() * info[0]->mat->Ka;
            if (s < 1 && s > 0) color = computeShadowColor(scene, light, info[0]->p, s, info[0], color);
        }
        if (s < 1){
            return color;
        }
    }
    for (auto light : lights)
    {
        vec3 l = light->vectorL(info[0]->p); //Calculem el vector L. 
        vec3 v = lookFrom - info[0]->p; //Calculem el vector V
        vec3 n = info[0]->normal; //Calculem el vector N
        l = glm::normalize(l); //Normalize the L vector
        v = glm::normalize(v); //Normalitzem el vector V
        n = glm::normalize(n); //Normalitzem el vector N
        vec3 h = glm::normalize(l + v);
        float spotDot = pow((glm::max(float(0.0), dot(n, h))), info[0]->mat->shininess) > 0.95 ? 1.0 : 0;
        float rimDot = (1 - dot(v, n) > 0.75) ? 1.0 : 0;

        float intensity = dot(l, n);
        if (intensity > 0.95) color = info[0] -> mat -> Kd;
        else if (intensity > 0.5) color = info[0] -> mat -> Kd * 0.6f;
        else if (intensity > 0.25) color = info[0] -> mat -> Kd * 0.4f;
        else color = info[0] -> mat -> Kd * 0.2f;

        color += light->getIa() * info[0]->mat->Ka; // Ambient
        color += light->getIs() * info[0]->mat->Ks * spotDot; // Specular
        color += light->getIs() * info[0]->mat->Kd * rimDot * intensity; // Rim
    }
    color += globalLight * info[0]->mat->Ka; //Calcul del color ambient global
    color = glm::clamp(color, 0.0f, 1.0f);
    
    return color;
}