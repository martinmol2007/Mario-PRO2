#ifndef FINDER_HH
#define FINDER_HH

// Tamaño de los chuncks del Finder
const static int ancho = 100;

#include <map>
#include <set>

#include "geometry.hh"

template <typename T>
class Finder {
    // el T es un objecte (template)
    std::map<const T*, std::set<pro2::Pt>> f_objs_; // para los objetos
    std::map<pro2::Pt, std::set<const T*>> f_bloques_; //  para saber que objetos hay en un cudrado (querry) (rectangulos)
public:
    Finder() {}

    void add(const T* t) { 
        // Conseguir el rectangulo
        pro2::Rect r = t->get_rect();

        // Calcular en que bloques (chuncks) esta Rect r
        // Devuelve set<Pt (chuncks)>
        // Añadir a f_objs_ con set<Pt>
        // Añadir en cada punto del set el objeto t


    }     
    void remove(const T* t) {
        // Buscar T en el f_objs_
        // Si esta, recorrer el set<Pt> eliminando el objeto (en el otro map (f_bloques))
        // Borrar t de f_objs_
    }
    void update(const T* t) {
        remove(t);
        add(t);
    }

    /**
     * @brief Retorna el conjunt d'objectes amb rectangles total o
     *        parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el cost
     * de l'algorisme ha de ser O(log n).
     *
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un rectangle
     *          parcial o totalment dins de `rect`
     */
    std::set<const T*> query(pro2::Rect rect) const {
        // Calcular en que bloques esta Rect (nos devuelve un set de puntos)
        // Para cada punto,  buscar en f_bloques_ y ver que objetos hay e irlos añadiendo al set
    }
};

/*
NOTAS:
Casillas que separan la camara
- Dos maps
map<obj., pts>
mpa<pt, objs>

*/

#endif