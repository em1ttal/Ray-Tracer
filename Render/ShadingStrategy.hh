#pragma once

#include "Scene.hh"
#include "Light.hh"
#include "AreaLight.hh"
#include "PointLight.hh"
#include <random>

class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {


        return vec3(0.0, 0.0, 0.0);
    };

    // TUTORIAL 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    float computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point) 
    {
        float fOmbra = 1.0f;
        if (dynamic_pointer_cast<AreaLight>(light) != nullptr) {
            fOmbra = 0.0f;
            vector<PointLight> pointLights = dynamic_pointer_cast<AreaLight>(light)->getPointLights();
            for (int i = 0; i < (int) pointLights.size(); i++) {
                vec3 L = normalize(pointLights[i].vectorL(point));
                Ray shadowRay(point, L, 0.01f, pointLights[i].distanceToLight(point));
                if (scene->allHits(shadowRay, shadowRay.getTmin(), shadowRay.getTmax())) {
                    for (int i = 0; i < (int) shadowRay.getHitRecords().size(); i++) {
                        fOmbra += 0.0;
                    }
                } else fOmbra += 1.0;
            }
            fOmbra /= (float) pointLights.size();
        } else {
            vec3 L = normalize(light->vectorL(point));
            Ray shadowRay(point, L, 0.01f, light->distanceToLight(point));
            //point -= 0.01f;
            if (scene->allHits(shadowRay, shadowRay.getTmin(), shadowRay.getTmax())) {
                for (int i = 0; i < (int) shadowRay.getHitRecords().size(); i++) {
                    if (shadowRay.getHitRecords()[i]->mat->opacity == 0.0f || shadowRay.getHitRecords()[i]->mat->dmax == 0.0f) {
                        fOmbra = 0.0f;
                        break;
                    }
                    if (dot(shadowRay.getDirection(), shadowRay.getHitRecords()[i]->normal) < 0.0f && dot(shadowRay.getDirection(), shadowRay.getHitRecords()[i+1]->normal) > 0.0f){
                        float d = shadowRay.getHitRecords()[i+1]->t - shadowRay.getHitRecords()[i]->t;
                        float aux = d / shadowRay.getHitRecords()[i]->mat->dmax;
                        fOmbra *= 1 - glm::max(0.0f, aux);
                        i++;
                    }
                    else return 0.0f;
                }
            }
        }
        fOmbra = glm::max(0.0f, fOmbra);
        return fOmbra;
    };

    vec3 computeShadowColor(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point, float fOmbra, shared_ptr<HitRecord> surface, vec3 colorSoFar) 
    {
        if (dynamic_pointer_cast<AreaLight>(light) != nullptr) return colorSoFar*fOmbra;
     
        vec3 L = normalize(light->vectorL(point));
        Ray shadowRay(point, L, 0.01f, light->distanceToLight(point));
        scene->allHits(shadowRay, shadowRay.getTmin(), shadowRay.getTmax());

        vec3 color = vec3(0.0f);

        for (int i = 0; i < (int) shadowRay.getHitRecords().size(); i+=2)
            color += light->getId() * shadowRay.getHitRecords()[i]->mat->Kd * shadowRay.getHitRecords()[i]->mat->opacity * surface->mat->Kd * fOmbra;
        

        return color;
    };

    virtual ~ShadingStrategy() {};


    // Método para calcular la oclusión ambiental en un punto dado
    float computeAmbientOcclusion(const vec3& point, const Scene& scene)
    {
        const int numRays = 64; // Número de rayos a lanzar para calcular la oclusión ambiental
        float numHits = 0; // Contador de rayos que intersectan con objetos

        // Generador de números aleatorios
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0, 1.0);

        // Lanzar múltiples rayos desde el punto en direcciones aleatorias
        for (int i = 0; i < numRays; ++i) {
            // Generar una dirección de rayo aleatoria en la semiesfera superior
            float u = dis(gen);
            float v = dis(gen);
            float theta = 2.0 * M_PI * u;
            float phi = acos(1.0 - 2.0 * v);
            vec3 direction = vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
            // Corregir el punto para evitar auto-intersecciones
            vec3 corrected_point = point + 0.01f * direction;

            // Crear el rayo desde el punto en la dirección generada
            Ray ray(corrected_point, direction);

            // Comprobar si el rayo intersecta con algún objeto en la escena
            if (scene.hit(ray, ray.getTmin(),ray.getTmax())) {
                // Incrementar el contador de intersecciones
                numHits++;
            }
        }

        // Calcular el factor de oclusión como el número de rayos que no intersectan dividido por el número total de rayos lanzados
        return 1.0 - (numHits / numRays);
    };
};
