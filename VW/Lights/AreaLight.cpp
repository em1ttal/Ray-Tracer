#include "AreaLight.hh"

AreaLight::AreaLight(vec3 center, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c): Light(Ia, Id, Is) {
    this->p1 = center - vec3(0.5f, 0.5f, 0.5f);
    this->p2 = center + vec3(0.5f, 0.5f, 0.5f);
    this->a = a;
    this->b = b;
    this->c = c;
    this->center = center;
    createPointLights();
}

AreaLight::AreaLight(vec3 p1, vec3 p2, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c): Light(Ia, Id, Is) {
    this->p1 = p1;
    this->p2 = p2;
    this->a = a;
    this->b = b;
    this->c = c;
    this->center = (p1 + p2) / 2.0f;
    createPointLights();
}

vec3 AreaLight::getP1() {
    return this->p1;
}

vec3 AreaLight::getP2() {
    return this->p2;
}

vec3 AreaLight::getCenter() {
    return this->center;
}

vector<PointLight> AreaLight::getPointLights() {
    return this->pointLights;
}

vec3 AreaLight::vectorL(vec3 point) {
    return normalize(center - point);
}

float AreaLight::attenuation(vec3 point) {
    if (abs(a)<DBL_EPSILON && abs(b)<DBL_EPSILON  && abs(c)<DBL_EPSILON) {
        //Si tots els coeficients son 0 considerem que no hi ha atenuacio
        return 1.0f;
    }
    //Calculem la distancia entre el punt i la posicio de la llum
    float d = distance(point, center);
    return 1.0f/(c*d*d + b*d + a);
}

float AreaLight::distanceToLight(vec3 point) {
    return distance(point, center);
}

void AreaLight::read (const QJsonObject &json)
{
    Light::read(json);

    if (json.contains("p1") && json["p1"].isArray()) {
        QJsonArray auxVec = json["p1"].toArray();
        p1[0] = auxVec[0].toDouble();
        p1[1] = auxVec[1].toDouble();
        p1[2] = auxVec[2].toDouble();
    }
    if (json.contains("p2") && json["p2"].isArray()) {
        QJsonArray auxVec = json["p2"].toArray();
        p2[0] = auxVec[0].toDouble();
        p2[1] = auxVec[1].toDouble();
        p2[2] = auxVec[2].toDouble();
    }
    if (json.contains("center") && json["center"].isArray()) {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
    if (json.contains("a") && json["a"].isDouble())
        a = json["a"].toDouble();
    if (json.contains("b") && json["b"].isDouble())
        b = json["b"].toDouble();
    if (json.contains("c") && json["c"].isDouble())
        c = json["c"].toDouble();

    createPointLights();
}

//! [1]
void AreaLight::write(QJsonObject &json) const
{
    Light::write(json);
    QJsonArray auxArray;
    auxArray.append(p1[0]);auxArray.append(p1[1]);auxArray.append(p1[2]);
    json["p1"] = auxArray;
    auxArray = QJsonArray();
    auxArray.append(p2[0]);auxArray.append(p2[1]);auxArray.append(p2[2]);
    json["p2"] = auxArray;
    auxArray = QJsonArray();
    auxArray.append(center[0]);auxArray.append(center[1]);auxArray.append(center[2]);
    json["center"] = auxArray;
    json["a"] = a;
    json["b"] = b;
    json["c"] = c;
}
//! [1]

void AreaLight::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Point Light" << "\n";
    QTextStream(stdout) << indent + 2 << "p1:\t" << p1[0] << ", "<< p1[1] << ", "<< p1[2] << "\n";
    QTextStream(stdout) << indent + 2 << "p2:\t" << p2[0] << ", "<< p2[1] << ", "<< p2[2] << "\n";
    QTextStream(stdout) << indent + 2 << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent + 2 << "a:\t" << a << "\n";
    QTextStream(stdout) << indent + 2<< "b:\t" << b << "\n";
    QTextStream(stdout) << indent + 2 << "c:\t" << c << "\n";

}

void AreaLight::createPointLights()
{
    float xDist = abs(p2.x - p1.x);
    float yDist = abs(p2.y - p1.y);
    float zDist = abs(p2.z - p1.z);
    float xStep = xDist / 5.0f;
    float yStep = yDist / 5.0f;
    float zStep = zDist / 5.0f;

    float xStart = glm::min(p1.x, p2.x);
    float yStart = glm::min(p1.y, p2.y);
    float zStart = glm::min(p1.z, p2.z);

    for (float i = xStart; i <= xStart + xDist; i += xStep) {
        for (float j = yStart; j <= yStart + yDist; j += yStep) {
            for (float k = zStart; k <= zStart + zDist; k += zStep) {
                pointLights.push_back(PointLight(vec3(i, j, k), Ia, Id, Is, a, b, c));
            }
        }
    }
}