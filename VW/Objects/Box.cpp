#include "Box.hh"

Box::Box() {
    p1 = vec3(-1,-1,-1);
    p2 = vec3(1,1,1);
}

Box::Box(vec3 p1, vec3 p2) {
    this->p1 = p1;
    this->p2 = p2;
}

bool Box::hit(Ray &raig, float tmin, float tmax, bool bounding) const {
    
    vec3 vt0 = (p1 - raig.getOrigin()) / raig.getDirection();
    vec3 vt1 = (p2 - raig.getOrigin()) / raig.getDirection();

    vec3 ptmin = glm::min(vt0, vt1);
    vec3 ptmax = glm::max(vt0, vt1);

    float tminbox = glm::max(glm::max(ptmin.x, ptmin.y), ptmin.z);
    float tmaxbox = glm::min(glm::min(ptmax.x, ptmax.y), ptmax.z);

    if (tmaxbox < 0 || tmaxbox < tminbox || tminbox > tmax) return false; 
    

    float t = tminbox > tmin ? tminbox : tmaxbox;
    if (!bounding) {
        shared_ptr<HitRecord> hitRecord = make_shared<HitRecord>();
        hitRecord->t = t;
        hitRecord->p = raig.pointAt(t); 
        if (abs(hitRecord->p.x - p1.x) < 0.001f) hitRecord->normal = vec3(-1, 0, 0);
        else if (abs(hitRecord->p.x - p2.x) < 0.001f) hitRecord->normal = vec3(1, 0, 0);
        else if (abs(hitRecord->p.y - p1.y) < 0.001f) hitRecord->normal = vec3(0, -1, 0);
        else if (abs(hitRecord->p.y - p2.y) < 0.001f) hitRecord->normal = vec3(0, 1, 0);
        else if (abs(hitRecord->p.z - p1.z) < 0.001f) hitRecord->normal = vec3(0, 0, -1);
        else if (abs(hitRecord->p.z - p2.z) < 0.001f) hitRecord->normal = vec3(0, 0, 1);
        hitRecord->mat = material; 

        raig.insertHit(hitRecord);
    }

    return true;
}


vec3 Box::calculateNormal(const vec3 &p) const {
    vec3 normal;
    if (std::abs(p.x - p1.x) < 1e-6) normal = vec3(-1, 0, 0);
    else if (std::abs(p.x - p2.x) < 1e-6) normal = vec3(1, 0, 0);
    else if (std::abs(p.y - p1.y) < 1e-6) normal = vec3(0, -1, 0);
    else if (std::abs(p.y - p2.y) < 1e-6) normal = vec3(0, 1, 0);
    else if (std::abs(p.z - p1.z) < 1e-6) normal = vec3(0, 0, -1);
    else normal = vec3(0, 0, 1);
    return normal;
}

bool Box::allHits(Ray &ray, float tmin, float tmax) const
{
    bool hits = false;
    float tnear = -INFINITY;
    float tfar = INFINITY;

    for (int i = 0; i < 3; i++)
    {
        float t0 = (p1[i] - ray.getOrigin()[i]) / ray.getDirection()[i];
        float t1 = (p2[i] - ray.getOrigin()[i]) / ray.getDirection()[i];
        tnear = std::max(tnear, std::min(t0, t1));
        tfar = std::min(tfar, std::max(t0, t1));
        if (tfar < tnear) return false;
    }
    
    if ((tnear < tmax && tnear > tmin) || (tfar < tmax && tfar > tmin)) {
        shared_ptr<HitRecord> hitNear = make_shared<HitRecord>();
        hitNear->t = tnear;
        hitNear->p = ray.pointAt(tnear);
        hitNear->normal = calculateNormal(hitNear->p);
        hitNear->mat = material;
        ray.insertHit(hitNear);

        if (tfar < tmax && tfar > tmin && tfar != tnear) {
            shared_ptr<HitRecord> hitFar = make_shared<HitRecord>();
            hitFar->t = tfar;
            hitFar->p = ray.pointAt(tfar);
            hitFar->normal = calculateNormal(hitFar->p);
            hitFar->mat = material;
            ray.insertHit(hitFar);
        }

        hits = true;
    }

    return hits;
}

void Box::update(int nframe)
{
    // No fa res.
}

void Box::aplicaTG(shared_ptr<TG> tg)
{
    // No fa res.
}

void Box::read(const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("punt_min") && json["punt_min"].isArray()) 
    {
        QJsonArray p1Array = json["punt_min"].toArray();
        p1 = vec3(p1Array[0].toDouble(), p1Array[1].toDouble(), p1Array[2].toDouble());
    }
    
    if (json.contains("punt_max") && json["punt_max"].isArray()) 
    {
        QJsonArray p2Array = json["punt_max"].toArray();
        p2 = vec3(p2Array[0].toDouble(), p2Array[1].toDouble(), p2Array[2].toDouble());
    }
}

void Box::write(QJsonObject &json) const
{
    Object::write(json);
    QJsonArray p1Array;
    p1Array.push_back(p1[0]);
    p1Array.push_back(p1[1]);
    p1Array.push_back(p1[2]);
    json["p1"] = p1Array;
    QJsonArray p2Array;
    p2Array.push_back(p2[0]);
    p2Array.push_back(p2[1]);
    p2Array.push_back(p2[2]);
    json["p2"] = p2Array;
}

void Box::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "punt_min: " << p1.x << ", " << p1.y << ", " << p1.z << "\n";
    QTextStream(stdout) << indent << "punt_max: " << p2.x << ", " << p2.y << ", " << p2.z << "\n";
}