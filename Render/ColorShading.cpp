#include "ColorShading.hh"


vec3 ColorShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    if (!infos.empty()) {
        vec3 color = vec3(0.0f);
        if (shadow) {
            float s = 1.0f;
            for (auto light : lights) {
                s *= computeShadow(scene, light, infos[0]->p);
                color += light->getIa() * infos[0]->mat->Ka;
                if (s < 1 && s > 0) color = computeShadowColor(scene, light, infos[0]->p, s, infos[0], color += light->getIa() * infos[0]->mat->Ka);
            }
            if (s < 1) return color;
        }
        return infos[0]->mat->Kd;
    } else {
        // Tracta la situació on el vector infos és buit
        // Retorna un valor predeterminat o maneja-ho segons les teves necessitats.
        return vec3(0.0f);
    }
}
