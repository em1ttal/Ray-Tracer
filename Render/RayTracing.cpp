#include "RayTracing.hh"


RayTracing::RayTracing(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
}


void RayTracing::play() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {

            //TODO TUTORIAL 2: mostrejar més rajos per pixel segons el valor de "samples"
            vec3 color(0, 0, 0);
            for (int s = 0; s < setup->getSamples(); s++)
            {
                float u = (float(x)) / float(width) + glm::linearRand(float(0), 1/float(width));
                float v = (float(height -y)) / float(height) + glm::linearRand(-1/float(height), float(0));

                // CÀLCUL DEL RAIG EN COORDENADES DE MON
                Ray r = camera->computeRay(u, v);

                // CÀLCUL DEL COLOR FINAL DEL PIXEL
                color += this->getColorPixel(r, 0);
            }

            color /= float(setup->getSamples());

            // TODO TUTORIAL 2: Gamma correction
            color = vec3(sqrt(color.r), sqrt(color.g), sqrt(color.b));
            color *= 255;
            color = glm::clamp(color, vec3(0.0f), vec3(255.0f));
            setPixel(x, y, color);
        }
    }
}


void RayTracing::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** TUTORIAL 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** TUTORIAL 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** TUTORIAL 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracing::getColorPixel(Ray &ray, int depth) {

    int maxDepth = setup->getMAXDEPTH();

    vec3 colorBackground = vec3(0.0f);
    vec3 color = vec3(0.0f);
    vec3 unit_direction;
    HitRecord info;
    
    if (setup->getBackground()) {
        vec3 colorTop = setup -> getTopBackground();
        vec3 colorBottom = setup -> getDownBackground();
        vec3 ray2 = normalize(ray.getDirection());

        float t = 0.5f * (ray2.y + 1);
        colorBackground = t*colorTop + (1-t)*colorBottom;
        color = colorBackground;
    }

    if (setup -> getNHints()) {
        if (scene -> allHits(ray, ray.getTmin(), ray.getTmax())) {
            if (setup -> getShadingStrategy() != nullptr) {
                color = setup -> getShadingStrategy() -> shading(scene, ray.getHitRecords(), setup -> getCamera() -> getLookFrom(), setup -> getShadows(), setup -> getLights(), setup -> getGlobalLight());
                vec3 factor = ray.getHitRecords()[0] -> mat -> kt;
                for (int i = 1; i < (int) ray.getHitRecords().size()-1; i++) {
                    factor *= ray.getHitRecords()[i] -> mat -> kt;
                }
                color += factor * colorBackground;
            } else {
                color = ray.getHit(0) -> mat -> Kd;
            }
        }
    } else {
        if (scene->hit(ray, ray.getTmin(), ray.getTmax())) {
            // El mètode "hit" desa només el punt més proper a tmin
            if (setup->getShadingStrategy()!=nullptr) {
                color = setup -> getShadingStrategy() -> shading(scene, ray.getHitRecords(), setup -> getCamera() -> getLookFrom(), setup -> getShadows(), setup -> getLights(), setup -> getGlobalLight());
            } else {
                color = ray.getHit(0)->mat->Kd;
            }

            if (depth == maxDepth) return color;
            Ray *scatterRay = new Ray(ray);
            vec3 scatterColor = vec3(0.0f);
            if (ray.getHit(0)->mat->scatter(ray, 0, scatterColor, *scatterRay))
            {
                if (ray.getHit(0)->mat->opacity < 1){
                    color += scatterColor * this->getColorPixel(*scatterRay, depth+1);
                } else {
                    color = color * (vec3(1) - scatterColor) + scatterColor * this->getColorPixel(*scatterRay, depth+1);
                }
            }
        }
    }
    return color;
}


void RayTracing::init() {
    auto s = setup->getShadingStrategy();
}

