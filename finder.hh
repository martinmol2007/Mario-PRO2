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

    /**
     * @brief Añade al Finder todos los chunks a los que el objeto t pertenece, tambien los chunks en los que el objeto t esta
     * 
     * @param t Objeto generico
     */
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
            for (int j = chunk_top; j <= chunk_bottom; j++) {
                pro2::Pt chunk = {i, j};
                f_objs_[t].insert(chunk);
            }
        }

        // Guarda en f_bloques_ el objeto que hay en cada chunk al que pertenece
        // Crea un set auxiliar con todos los chunks a los que pertenece t
        std::set<pro2::Pt> chunks_objeto = f_objs_[t];

        for (auto it = chunks_objeto.begin(); it != chunks_objeto.end(); it++) {
            // Uno de los chunks a los que pertenece el objeto t
            pro2::Pt p = (*it);
            f_bloques_[p].insert(t);
        }

        return;
    }    

    /**
     * @brief Quita del finder los chunks a los que pertenece t y el objeto t
     * 
     * @param t Objeto generico
     */
    void remove(const T* t) {
        // Busca el objeto t para ver si esta
        auto it = f_objs_.find(t);
        
        // Si esta, lo borras de todo
        if(it != f_objs_.end()) {
            // Set auxiliar con todos los chunks a los que un objeto tiene
            const std::set<pro2::Pt> chunks_objeto = it->second;
            
            // Para cada chunk en el que esta, borras el objeto que esta en el map f_bloques en ese chunk
            for(auto it_set_chunks = chunks_objeto.begin(); it_set_chunks != chunks_objeto.end(); it_set_chunks++) {
                // Conseguir un Chunk
                pro2::Pt c = (*it_set_chunks);
              
                // Borra el objeto que esta en el chunk c del set de objetos
                f_bloques_[c].erase(t);
            }
            // Cuando has borrado el objeto t de todos los chunks en los que estaba, borrar t del mapa de objetos / puntos
            f_objs_.erase(it);
        }
        
        return;
    }

    /**
     * @brief Actualiza el finder, por ejemplo para el moviemiento de las monedas
     * 
     * @param t Objeto generico
     */
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
        // Calcular en que bloques (chunks) esta Rect (nos devuelve un set de puntos)
        // Para cada chunk,  buscar en f_bloques_ y ver que objetos hay e irlos añadiendo al set

        // Crea el set con todos los objetos que estan dentro del rectangulo (camara)
        std::set<const T*> objetos_visibles;

        // Crea un set para los chunks que hay dado un rectangulo
        std::set<pro2::Pt> chunks_rectangulo;

        int chunk_left = rect.left / CHUNK_MIDA;
        int chunk_right = rect.right / CHUNK_MIDA;
        int chunk_top = rect.top / CHUNK_MIDA;
        int chunk_bottom = rect.bottom / CHUNK_MIDA;

        for(int i  = chunk_left; i <= chunk_right; i++) {
            for(int j = chunk_top; j <= chunk_bottom; j++) {
                // Poner en el set todos los chunks que hay dado un rectangulo (rect)
                chunks_rectangulo.insert({i, j});
            }
        }


        // Para cada chunk de f_bloques_ en rect, poner en el set resultado todos los objetos que haya ahi
        for(auto it = chunks_rectangulo.begin(); it != chunks_rectangulo.end(); it++) {
            // Buscar si hay algun objeto en ese chunk
            auto it_bloques = f_bloques_.find(*it);

            if(it_bloques != f_bloques_.end()) {
                poner_set(objetos_visibles, it_bloques->second);
            }
        }
        

        // Devuelve un set con todos los objetos que estan visibles dado un rectangulo
        return objetos_visibles;
    }
private:
    /**
     * @brief Funcion auxiliar que pone en el set de objetos_visibles todo lo que haya en el set objetos
     * 
     */
    void poner_set(std::set<const T*>& objetos_visibles, const std::set<const T*>& objetos) const {
        for(auto it = objetos.begin(); it != objetos.end(); it++) {
            objetos_visibles.insert(*it);
        }
        return;
    }
};


#endif