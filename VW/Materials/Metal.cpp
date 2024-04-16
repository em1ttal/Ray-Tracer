#include "Metal.hh"

Metal::Metal(const vec3& color): Material()
{
    Kd = color;
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const float dm):
    Material(a, d, s, k, o, dm) {
}
Metal::~Metal(){}

bool Metal::scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const {
    vec3 reflectedVector = glm::reflect(r_in.getDirection(),r_in.getHit(t)->normal);
    r_out = Ray(r_in.getHit(t)->p+0.01f*reflectedVector, reflectedVector);
    color = Ks;
    return true;
    
}

vec3 Metal::getDiffuse(vec2 uv) const {
    return Kd;

}
