#pragma once

#include "Object.hh"
#include "../TG/TranslateTG.hh"

class Box: public Object  {
public:
    Box();

    Box(vec3 p1, vec3 p2);

    virtual ~Box() {}
    virtual bool hit(Ray& r, float tmin, float tmax, bool bounding = false) const;
    virtual bool allHits(Ray& r, float tmin, float tmax) const;

    virtual void update(int nframe) override;
    virtual vec3 calculateNormal(const vec3 &p) const;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;



private:
    vec3 p1;
    vec3 p2;

};