#include "Transparent.hh"

Transparent::Transparent(const vec3& color): Material()
{
    Kd = color;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const float dm, const float nut):
    Material(a, d, s, k, o, dm) {
    this->nut = nut;
}
Transparent::~Transparent(){}

bool Transparent::scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const {
    float epsilon = 0.0001;
    vec3 normal;
    float ratio;
    if (glm::dot(r_in.getDirection(), r_in.getHit(0)->normal) > 0){
        normal = -r_in.getHit(0)->normal;
        ratio = nut;
    }else{
        normal = r_in.getHit(0)->normal;
        ratio = 1.0f / nut;
    }
    
    vec3 auxRay = glm::refract(r_in.getDirection(), normal, ratio);
    if (length(auxRay) < epsilon){
        auxRay = glm::reflect(r_in.getDirection(), normal);
        color = this->Ks;
    } else color = this->kt;

    r_out = Ray(r_in.getHit(0)->p+0.01f*auxRay, auxRay);
    return true;
}

vec3 Transparent::getDiffuse(vec2 uv) const {
    return Kd;

}
