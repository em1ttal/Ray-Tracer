#pragma once

#include "Object.hh"
#include "../TG/TranslateTG.hh"

class Triangle: public Object  {
public:
    Triangle();

    Triangle(vec3 p1, vec3 p2, vec3 p3);

    virtual ~Triangle() {}
    virtual bool hit(Ray& r, float tmin, float tmax, bool bounding = false) const;
    virtual bool allHits(Ray& r, float tmin, float tmax) const;

    virtual void update(int nframe) override;
    virtual vec3 calculateNormal() const;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;



private:
    vec3 p1;
    vec3 p2;
    vec3 p3;
    vec3 normal;
};