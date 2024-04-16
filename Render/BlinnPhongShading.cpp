#include "BlinnPhongShading.hh"


vec3 BlinnPhongShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    if (infos.empty()) {
        auto m = infos[0]->mat;
        return m->Kd;
    }

    vec3 totalColor = vec3(0.0f);
    for (auto light : lights)
    {
        vec3 aux = vec3(0.0f);
        vec3 l = light->vectorL(infos[0]->p); //Calculem el vector L. 
        vec3 v = lookFrom - infos[0]->p; //Calculem el vector V
        vec3 n = infos[0]->normal; //Calculem el vector N
        l = glm::normalize(l); //Normalize the L vector
        v = glm::normalize(v); //Normalitzem el vector V
        n = glm::normalize(n); //Normalitzem el vector N
        vec3 h = glm::normalize(l + v);
        
        aux += light->getId() * infos[0]->mat->Kd * glm::max(0.0f, glm::dot(l, n)); //Calcul del color difús
        aux += light->getIs() * infos[0]->mat->Ks * pow(glm::max(0.0f, glm::dot(n, h)), infos[0]->mat->shininess); //Calcul del color especular
        aux *= light->attenuation(infos[0]->p); //Calcul de l'atenuació
        if (shadow) {
            float fOmbra = computeShadow(scene, light, infos[0]->p); //Calcul de l'ombra
            if (fOmbra == 0.0f || fOmbra == 1.0f) {
                aux *= fOmbra;
            }
            else aux = computeShadowColor(scene, light, infos[0]->p, fOmbra, infos[0], aux);
        }
        aux += light->getIa() * infos[0]->mat->Ka * computeAmbientOcclusion(infos[0]->p, *scene); //Calcul del color ambient
        totalColor += aux;
    }
    totalColor += globalLight * infos[0]->mat->Ka; //Calcul del color ambient global
    return totalColor;
}
