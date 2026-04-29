#ifndef MONEDA__HH
#define MONEDA__HH

#include "window.hh"

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
     * @brief Genera un rectangulo de la Hitbox de la moneda
     * 
     * @return Hitbox de la moneda
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Devuelve la posicion x de la moneda
     * 
     * @return Posicion x
     */
    int get_pos_x() const;

    /**
     * @brief Devuelve la posicion y de la moneda
     * 
     * @return Posicion y
     */
    int get_pos_y() const;

    /**
     * @brief Devuelve la posicion xoffset de la moneda
     * 
     * @return Posicion xoffset
     */
    int get_xoffset() const;
    
private:
    /**
     * @brief Sprite de la moneda
     * 
     */
    static const vector<vector<int>> sprite_moneda;
};



#endif