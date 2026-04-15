#ifndef MONEDA__HH
#define MONEDA__HH

#include "window.hh"
#include "mario.hh"

#include <iostream>
#include <vector>

using namespace std;
using namespace pro2;

class Moneda {
private:
    /**
     * @brief Posicion de la moneda
     * 
     */
    Pt pos_;

    /**
     * @brief Offset (Variable que indica el desplazamiento horizontal de la moneda respecto a pos_)
     * 
     */
    int xoffset_;

    /**
     * @brief Booleano que indica si esta encima
     * 
     */
    bool encima_;

public:
    /**
     * @brief Construye un objeto Moneda con pos
     * 
     * @param pos Posicion de la moneda
     */
    Moneda(Pt pos);

    /**
     * @brief Pinta la moneda
     * 
     * @param window 
     */
    void paint(pro2::Window & window) const;

    /**
     * @brief Actualiza la "animacion" de la moneda
     * 
     */
    void update();

    /**
     * @brief Mira si Mario y la Moneda estan en contacto 
     * 
     * @param mario Mario
     * @return true Si Mario ha cogido la moneda 
     * @return false Si Mario no ha codigo la moneda
     */
    bool chocan (Mario& mario) const;
    
private:
    /**
     * @brief Sprite de la moneda
     * 
     */
    static const vector<vector<int>> sprite_moneda;
};



#endif