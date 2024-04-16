#include "Scene.hh"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}


bool Scene::hit(Ray &raig, float tmin, float tmax, bool bounding) const {
    // TO DO TUTORIAL 0 i TUTORIAL 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, cal actualitzar la llista de  HitRecords que conte el raig
    
    bool hit = false;
    float aux = tmax;
    shared_ptr<HitRecord> closest = nullptr;
    for (const auto& obj : objects) {
        if (obj->hit(raig, tmin, aux)) {
            hit = true;
            aux = raig.getHitRecords()[0]->t;
            closest = raig.getHitRecords()[0];
        }
    }
    if (closest)
    {
        raig.insertHit(closest);
    }
    

    return hit;
}

bool Scene::allHits(Ray& r, float tmin, float tmax) const
{
    // TO DO TUTORIAL 0 i TUTORIAL 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb totes
    // les interseccions
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitRecord conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'afegir un nou HitRecord del raig.
    vector<shared_ptr<HitRecord>> all;
    for (const auto& obj : objects)
    {
        obj->allHits(r, tmin, tmax);
    }
    for(const auto& hit: r.getHitRecords())
    {
        all.push_back(hit);
    }
    sort(all.begin(),all.end(), [](const shared_ptr<HitRecord>& a,
    const shared_ptr<HitRecord>& b){
        return a->t < b->t;
    });
    r.getHitRecords() = all;
    
    return !all.empty();
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::aplicaTG(shared_ptr<TG> tg) {
    // TO DO
}

bool Scene::showBoundingVolumes(bool show) {
    if (show)
    {
        for (const auto& obj : objects)
        {
            if (dynamic_cast<Mesh*>(obj.get()) == nullptr) continue;
            objects.push_back(make_shared<Box>(dynamic_pointer_cast<Mesh>(obj)->getBoundingBox()));
            //objects.push_back(make_shared<Sphere>(dynamic_pointer_cast<Mesh>(obj)->getBoundingSphere()));
        }
    } else {
        for (const auto& obj : objects)
        {
            if (dynamic_cast<Mesh*>(obj.get()) == nullptr) continue;
            objects.pop_back();
        }
    }
    return true;
}