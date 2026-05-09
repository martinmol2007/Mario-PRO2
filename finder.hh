#ifndef FINDER_HH
#define FINDER_HH

// Tamaño de los chuncks del Finder

static const int CHUNK_MIDA = 100;

#include <map>
#include <set>

#include "geometry.hh"

template <typename T>
class Finder {
    /**
     * @brief Map; que segun un objeto, te dice en que chunks esta
     * 
     */
    std::map<const T*, std::set<pro2::Pt>> f_objs_; 

    /**
     * @brief Map; que segun un chunk te dice que objetos hay dentro de ese chunk
     * 
     */
    std::map<pro2::Pt, std::set<const T*>> f_bloques_; 
public:
    Finder() {}

    void add(const T* t) { 
        // Conseguir el rectangulo
        pro2::Rect r_pos = t->get_rect();

        // Calcula a que chunk pertenece el objeto segun su rectangulo
        int chunk_left = r_pos.left / CHUNK_MIDA;
        int chunk_right = r_pos.right / CHUNK_MIDA;
        int chunk_top = r_pos.top / CHUNK_MIDA;
        int chunk_bottom = r_pos.bottom / CHUNK_MIDA;

        // Guarda en f_objs_ los chunks en los que esta t (lo del set)
        for (int i = chunk_left; i <= chunk_right; i++) {
            for (int j = chunk_top; j <= chunk_top; j++) {
                pro2::Pt chunk = {i, j};
                f_objs_[t].insert(chunk);
            }
        }

        std::set<pro2::Pt> chunks_objeto = f_objs_[t];

        for (auto it = chunks_objeto.begin(); it != chunks_objeto.end(); it++) {
            pro2::Pt p = (*it);
            f_bloques_[p].insert(t);
        }


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