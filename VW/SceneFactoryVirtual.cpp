#include "SceneFactoryVirtual.hh"


SceneFactoryVirtual::SceneFactoryVirtual():SceneFactory()
{

}

SceneFactoryVirtual::SceneFactoryVirtual(QString filename) {
    createScene(filename);
}

shared_ptr<Scene>  SceneFactoryVirtual::createScene() {
    scene= make_shared<Scene>();
    // Pots posar el codi aqui per generar una escena de forma procedimental
    
    auto base = make_shared<Box>(vec3(-20,-9,-20), vec3(20,2,20));
    auto mat1 = MaterialFactory::getInstance().createMaterial(vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), glm::linearRand(5.0F, 15.0F), glm::linearRand(0.0F, 1.0F), glm::linearRand(1.0F, 1.5F), static_cast<MaterialFactory::MATERIAL_TYPES>(1));
    base->setMaterial(mat1);
    scene->objects.push_back(base);

    auto monolith = make_shared<Box>(vec3(-6, 2, -2), vec3(-3, 9, 0));
    auto mat2 = MaterialFactory::getInstance().createMaterial(vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), glm::linearRand(5.0F, 15.0F), glm::linearRand(0.0F, 1.0F), glm::linearRand(1.0F, 1.5F), static_cast<MaterialFactory::MATERIAL_TYPES>(2));
    mat2->opacity = 1.0;
    mat2->nut = 1.5;
    monolith->setMaterial(mat2);    
    scene->objects.push_back(monolith);

    OneSphere(scene, vec3(-1, 3, 1), 1);
    auto sphere = make_shared<Sphere>(vec3(-1, 3, 1), 1);
    auto mat3 = MaterialFactory::getInstance().createMaterial(vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0),glm::linearRand(0.0, 1.0)), glm::linearRand(5.0F, 15.0F), glm::linearRand(0.0F, 1.0F), glm::linearRand(1.0F, 1.5F), static_cast<MaterialFactory::MATERIAL_TYPES>(0));
    sphere->setMaterial(mat3);    
    scene->objects.push_back(sphere);
    
    return scene;
}

shared_ptr<SetUp>  SceneFactoryVirtual::createSetup() {
    auto setup = make_shared<SetUp>();
    setup->setCamera(make_shared<Camera>(vec3(-2, 4, 8), vec3(-2, 2, 0), vec3(0, 1, 0), 90, 2.0, 600, 0, 0));
    setup->setLights(vector<shared_ptr<Light>>({make_shared<PointLight>(vec3(2, 8, 10), vec3(0.3), vec3(0.7), vec3(1.0), 0.0, 0.0, 0.5)}));
    setup->setShadows(true);
    setup->setMAXDEPTH(5);
    setup->setSamples(10);

    return setup;
}

shared_ptr<Scene> SceneFactoryVirtual::createScene(QString filename) {

    scene= make_shared<Scene>();
    load(filename);
    print(0);

    return scene;
}


void SceneFactoryVirtual::OneSphere(shared_ptr<Scene> s, vec3 position, float radius) {
    auto sphere = make_shared<Sphere>(position, radius);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    s->objects.push_back(sphere);

}

void SceneFactoryVirtual::OneBox(shared_ptr<Scene> s, vec3 p1, vec3 p2) {
    auto box = make_shared<Box>(p1, p2);
    box->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    s->objects.push_back(box);
}

void SceneFactoryVirtual::OneTriangle(shared_ptr<Scene> s, vec3 p1, vec3 p2, vec3 p3) {
    auto triangle = make_shared<Triangle>(p1, p2, p3);
    triangle->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    s->objects.push_back(triangle);
}

//! [3]
bool SceneFactoryVirtual::load(QString nameFile)
{
    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the virtual scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json virtual scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded virtual scene using " << "...\n";
    return true;
}
//! [3]

//! [4]
bool SceneFactoryVirtual::save(QString nameFile) const
{
    QFile saveFile(QString(nameFile.append(".json")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open virtual scene file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(QJsonDocument(setUpObject).toJson());

    return true;
}

//! [0]
void SceneFactoryVirtual::read(const QJsonObject &json)
{
    if (json.contains("scene") && json["scene"].isString())
        scene->name = json["scene"].toString();
    if (json.contains("typeScene") && json["typeScene"].isString())
        currentType = getSceneFactoryType(json["typeScene"].toString());

    if (json.contains("objects") && json["objects"].isArray()) {
        QJsonArray objectsArray = json["objects"].toArray();

        for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex++) {
            QJsonObject objectObject = objectsArray[objectIndex].toObject();
            shared_ptr<Object> o;
            if (objectObject.contains("type") && objectObject["type"].isString()) {
                QString objStr = objectObject["type"].toString().toUpper();
                o = ObjectFactory::getInstance().createObject(ObjectFactory::getInstance().getObjectType(objStr));
                o->read(objectObject);
                scene->objects.push_back(o);
            }
        }
    }

}
//! [0]

void SceneFactoryVirtual:: write(QJsonObject &json) const
{
   json["scene"] = scene->name;
   json["typeScene"] = SceneFactory::getNameType(currentType);


    QJsonArray objectsArray;
    for (const shared_ptr<Object> &o : scene->objects) {
        QJsonObject objectObject;
        int  value = ObjectFactory::getInstance().getIndexType (o);
        QString className = ObjectFactory::getInstance().getNameType(value);

        o->write(objectObject);
        objectObject["type"] = className;
        objectsArray.append(objectObject);
    }
    json["objects"] = objectsArray;
}

void SceneFactoryVirtual::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "scene:\t" << scene->name << "\n";
    QTextStream(stdout) << indent << "typeScene:\t" << getNameType(currentType) << "\n";

    QTextStream(stdout) << indent << "Objects:\t\n";
    for (unsigned int i =0; i< scene->objects.size(); i++) {
        auto value = ObjectFactory::getInstance().getIndexType (scene->objects[i]);
        QString className = ObjectFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "name:\t" << scene->objects[i]->name <<"\n";
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";
        scene->objects[i]->print(2);
    }
 }
