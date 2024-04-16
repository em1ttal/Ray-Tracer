# RayTracingToy
Pràctica 1 - GiVD 2023-24

En aquest fitxer cal que feu l'informe de la pràctica 1.

## Equip:
**B02**
* Eshaan Mittal
* Adria Gasull Rectoret
* Daniel Gonzalez Braza
* Paula Bezares Cano

### Features (marqueu les que heu fet i qui les ha fet)
- Tutorial 0
    - [x] Background amb degradat
      - Eshaan Mittal
    - [x] Color Shading
      - Eshaan Mittal
    - [x] Normal Shading
      - Eshaan Mittal
    - [x] Creació d'una escena procedimentalment
      - Eshaan Mittal
    - [x] Creació d'una escena via fitxer json
      - Eshaan Mittal
 - Tutorial 1
   - [x] Intersecció amb l'escena
      -  Paula Bezares, Eshaan Mittal
   - [x] Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [x] Hit Box
          - EAdria Gasull, Daniel Gonzalez
        - [x] Hit Triangle
          - Eshaan Mittal, Daniel Gonzalez, Adria Gasull
        - [x] Hit Malla
          - Eshaan Mittal, Paula Bezares
   - [x] Exploració del Raig via multiples hits
     - Eshaan Mittal
   - [x] Ray Marching
     - Eshaan Mittal
       
- Tutorial 2
  - [x] Shadings bàsics
    - Paula Bezares
  - [x] Ombres
    - Eshaan Mittal, Paula Bezares
  - [x] Penombres amb llums amb volum
    -  Eshaan Mittal
  - [x] Ambient occlusion
    - Eshaan Mittal, Paula Bezares

- Tutorial 3
  - [x] Reflexions 
    - Eshaan Mittal, Paula Bezares
  - [x] Transparències
    - Eshaan Mittal, Paula Bezares
  - [x] Visualitzar els Bounding Volumes
    - Eshaan Mittal
  - [x] Environmental mapping
    - Eshaan Mittal

- [ ] Opcionals
- [ ] Preparació de l'escena final
- [ ] Evaluació de l'eficiència de les optimitzacions en diferents escenes

### Explicació de la pràctica    
  * **Organització de la pràctica**
    * Hemos organizado la practica haciendo los apartados que podiamos en el momento que nos poniamos. Muchas veces trabajabamos juntos con el mismo ordenador para que todos los que estaban veian lo que estabamos haciendo.
  
  * **Decisions a destacar**
    * Comenteu les decisions que heu pres 
### Screenshots de cada fase
Los imagenes no salen bien en el pdf del readme. Se tendran que ver en github.
* **Tutorial 0**:
  
      · Degradat:
    <div align="center">
        <img width="60%" src="Screenshots/degradat.png"></img>
    </div>
  
      · Esfera unitaria:
    <div align="center">
        <img width="60%" src="Screenshots/oneSphere.png"></img>
    </div>
  
      · Esfera amb Normal Shading
    <div align="center">
        <img width="60%" src="Screenshots/oneShpereNormal.png"></img>
    </div>

      · Escena amb esferes
    <div align="center">
        <img width="60%" src="Screenshots/myScene.png"></img>
    </div>


* **Tutorial 1**:
  
      · Escena amb diferents objectes
    <div align="center">
        <img width="60%" src="Screenshots/twoSpheres.png"></img>
    </div>

      · AllHits oneEsphere
    <div align="center">
        <img width="40%" src="Screenshots/closest_hit(1).png"></img>
        <img width="40%" src="Screenshots/01kt.png"></img>
        <img width="40%" src="Screenshots/05kt.png"></img>
        <img width="40%" src="Screenshots/09kt.png"></img>
    </div>

      · AllHits twoSpheres
    <div align="center">
        <img width="60%" src="Screenshots/twoSphereAll.png"></img>
    </div>

      · Box
    <div align="center">
        <img width="60%" src="Screenshots/box.png"></img>
    </div>
  
      · Triangle
    <div align="center">
        <img width="60%" src="Screenshots/triangle.png"></img>
    </div>

      · Mesh
    <div align="center">
        <img width="60%" src="Screenshots/mesh.png"></img>
    </div>

      · Acceleracions
    <div align="center">
        <img width="40%" src="Screenshots/meshBox.png"></img>
        <img width="40%" src="Screenshots/meshSphere.png"></img>
    </div>

* **Tutorial 2**:
  
        · Component ambient
    <div align="center">
        <img width="60%" src="Screenshots/Component_ambient.png"></img>
    </div>

      · Component Difosa
    <div align="center">
        <img width="60%" src="Screenshots/Component_difosa.png"></img>
    </div>
  
      · Component Especular
    <div align="center">
        <img width="60%" src="Screenshots/Component_especular.png"></img>
    </div>

      · Combinació de les 3 components
    <div align="center">
        <img width="60%" src="Screenshots/Combina_les_tres.png"></img>
    </div>

      · Atenua en profunditat
    <div align="center">
        <img width="40%" src="Screenshots/Atenua_en_profunditat.png"></img>
    </div>
    
      · Llum global
    <div align="center">
        <img width="60%" src="Screenshots/Llum_global.png"></img>
    </div>

      · Shadows with Color Shading
    <div align="center">
        <img width="40%" src="Screenshots/ColorShading.png"></img>
    </div>

      · Shadows with Normal Shading
    <div align="center">
        <img width="40%" src="Screenshots/NormalShading.png"></img>
    </div>

      · Shadows with Cel/Toon Shading
    <div align="center">
        <img width="40%" src="Screenshots/CelShading.png"></img>
    </div>

* **Tutorial 3**:
  
      · Lambertian Sphere with Max Depth 10
    <div align="center">
        <img width="60%" src="Screenshots/Lambertian.png"></img>
    </div>
  
      · Reflexions Metàliques with Max Depth 10
    <div align="center">
        <img width="60%" src="Screenshots/ReflexionsMetaliques.jpeg"></img>
    </div>

      · Esferes de metall transparents with Max Depth 3
    <div align="center">
        <img width="60%" src="Screenshots/espheres_metal_transp.png"></img>
    </div>

      · Transparències 4 esferes with Max Depth 4
    <div align="center">
        <img width="40%" src="Screenshots/FourSpheres.jpeg"></img>
    </div>
    
      · Procedurally Generated Scene
    <div align="center">
        <img width="60%" src="Screenshots/setupNewMaterial.jpeg"></img>
    </div>

      · Our Json Scene (escenaPrueba.json and setupRenderEscenaPrueba.json)
    <div align="center">
        <img width="60%" src="Screenshots/json scene.png"></img>
    </div>
    Nuestra escena base que aun no esta acabado. Son dos cubos de metal uno de material definido como Chrome y el otro como Gold, reflejando el otro.

      · Comparison of Blinn-Phong Transparent(Left) and All Hits Transparent(Right)
    <div align="center">
        <img width="40%" src="Screenshots/espheres_metal_transp.png"></img>
        <img width="40%" src="Screenshots/metaltransp all hits.png"></img>
    </div>
    A la izquierda, se emplea el modelo de sombreado Blinn-Phong, que produce reflejos especulares más nítidos y reflejos más claros, ofreciendo un acabado pulido y brillante a los objetos transparentes. Este efecto se logra utilizando el vector intermedio entre la vista y las direcciones de la luz para un cálculo eficiente de la reflexión especular. A la derecha, se utiliza un método más simple, que calcula múltiples intersecciones de los rayos de luz a través de materiales transparentes, solo considerando los componentes kt y Kd del material. Además, no consideramos ningún reflejo o refracción de los rayos de luz, es decir, viajan en línea recta, lo que lo convierte en una forma más rápida de representar una imagen. 


* **Opcionals**:


* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades 
   i de configuració que heu fet servir
