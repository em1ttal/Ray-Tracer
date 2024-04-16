#include "Sphere.hh"

Sphere::Sphere() {
    center=vec3(0.0,0.0,0.0);
    radius = 1.0;
}

Sphere::Sphere(vec3 cen, float r)  {
    center = cen;
    radius = r;
}

bool Sphere::hit(Ray &raig, float tmin, float tmax, bool bounding) const {
    shared_ptr<HitRecord> hit = make_shared<HitRecord>();

    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < tmax && temp > tmin) {
            hit->t = temp;
            hit->p = raig.pointAt(hit->t);
            hit->normal = (hit->p - center) / radius;
            hit->mat = material;
            if (!bounding) raig.insertHit(hit);
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin) {
            hit->t = temp;
            hit->p = raig.pointAt(hit->t);
            hit->normal = (hit->p - center) / radius;
            hit->mat= material;
            if (!bounding) raig.insertHit(hit);
            return true;
        }
    }
    return false;
}

bool Sphere::allHits(Ray& raig, float tmin, float tmax) const {

    shared_ptr<HitRecord> info1 = make_shared<HitRecord>();

    bool trobat = false;
    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < tmax && temp > tmin) {
            info1->t = temp;
            info1->p = raig.pointAt(info1->t);
            info1->normal = (info1->p - center) / radius;
            info1->mat = material;
            raig.addHit(info1);
            trobat = true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin) {
            shared_ptr<HitRecord> info2 = make_shared<HitRecord>();
            info2->t = temp;
            info2->p = raig.pointAt(info2->t);
            info2->normal = (info2->p - center) / radius;
            info2->mat = material;
            raig.insertHit(info2);
            trobat = true;
        }
    }
    return trobat;
}

void Sphere::update(int frame) {
    // TO DO: Cal ampliar-lo per a fer el update de l'esfera
}

void Sphere::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es fan les translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Sphere::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("radius") && json["radius"].isDouble()) {
        radius = json["radius"].toDouble();
    }
    if (json.contains("center") && json["center"].isArray()) {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Sphere::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);auxArray.append(center[1]);auxArray.append(center[2]);
    json["center"] = auxArray;

    json["radius"] = radius;
}
//! [1]

void Sphere::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent << "radius:\t" << radius<< "\n";
}

