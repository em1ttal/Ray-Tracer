#include <QVector>
#include <QVector3D>

#include "Mesh.hh"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();
    if (triangles.size() > 0) triangles.clear();

}

void Mesh::makeTriangles() {
    // TO DO Fase 1: A implementar
    triangles.clear();
    for (const auto& face : cares) {
        vec4 v0 = vertexs[face.idxVertices[0]];
        vec4 v1 = vertexs[face.idxVertices[1]];
        vec4 v2 = vertexs[face.idxVertices[2]];
        vec3 p0 = vec3(v0.x, v0.y, v0.z);
        vec3 p1 = vec3(v1.x, v1.y, v1.z);
        vec3 p2 = vec3(v2.x, v2.y, v2.z);
        Triangle triangle(p0, p1, p2);
        triangle.setMaterial(this -> getMaterial());
        triangles.push_back(triangle);
    }
}

void Mesh::makeBoundingBox()
{
    // TO DO Fase 1: A implementar
    vec3 pmin = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    vec3 pmax = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (const auto& vertex : vertexs) {
        pmin.x = std::min(pmin.x, vertex.x);
        pmin.y = std::min(pmin.y, vertex.y);
        pmin.z = std::min(pmin.z, vertex.z);
        pmax.x = std::max(pmax.x, vertex.x);
        pmax.y = std::max(pmax.y, vertex.y);
        pmax.z = std::max(pmax.z, vertex.z);
    }
    boundingBox = Box(pmin, pmax);
    boundingBox.setMaterial(make_shared<Lambertian>(vec3(1, 0, 0)));
    boundingBox.getMaterial()->kt = vec3(0.8f);
}

void Mesh::makeBoundingSphere()
{
    // TO DO Fase 1: A implementar
    vec3 center = vec3(0.0f, 0.0f, 0.0f);
    float radius = 0.0f;
    for (const auto& vertex : vertexs) {
        center += vec3(vertex.x, vertex.y, vertex.z);
    }
    center /= vertexs.size();
    for (const auto& vertex : vertexs) {
        vec3 p = vec3(vertex.x, vertex.y, vertex.z);
        float d = length(p - center);
        if (d > radius) radius = d;
    }
    boundingSphere = Sphere(center, radius);
    boundingSphere.setMaterial(make_shared<Lambertian>(vec3(1, 0, 0)));
    boundingSphere.getMaterial()->kt = vec3(0.8f);
}

bool Mesh::hit(Ray& raig, float tmin, float tmax, bool bounding) const {
    bool hit = false;
    if (!boundingBox.hit(raig, tmin, tmax, true)) return false;
    //if (!boundingSphere.hit(raig, tmin, tmax, true)) return false;
    float aux = tmax;
    shared_ptr<HitRecord> closest = nullptr;
    for (const auto& triangle : triangles) {
        if (triangle.hit(raig, tmin, aux)) {
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

bool Mesh::allHits(Ray& raig, float tmin, float tmax) const {
    // TODO Tutorial 1: A implementar
    bool hits = false;
    if (!boundingBox.hit(raig, tmin, tmax, true)) return false;
    //if (!boundingSphere.hit(raig, tmin, tmax, true)) return false;
    for (const auto& triangle : triangles) {
        if (triangle.hit(raig, tmin, tmax)) {
            raig.insertHit(raig.getHit(0));
            hits = true;
        }
    }
    return hits;
}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
}

void Mesh::update(int frame) {
    // TO DO: Cal ampliar-lo per a fer el update de la mesh
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*face);
                    }
                }
            }
            file.close();
            makeTriangles();
            makeBoundingBox();
            makeBoundingSphere();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



