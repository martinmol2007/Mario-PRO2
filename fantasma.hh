#ifndef FANTASMA__HH
#define FANTASMA__HH

#include "window.hh"
#include "utils.hh"
#include <vector>
#include <cmath>


class Fantasma {
private:
    /**
     * @brief Posicion del fantasma
     * 
     */
    pro2::Pt pos_;

    /**
     * @brief Offset de la posicion x (para el movimiento horizontal)
     * 
     */
    double xoffset_;

    /**
     * @brief Offset de la posicion y (para el movimiento vertical)
     * 
     */
    double yoffset_;

    /**
     * @brief Direccion de movimiento del fantasma
     * 
     */
    double direccion = 0.5;
public:
    /**
     * @brief Constructor del Fantasma
     * 
     * @param pos Posicion de aparicion del Fantasma
     */
    Fantasma(pro2::Pt pos);

    /**
     * @brief Pinta el Fantsma por pantalla
     * 
     * @param window Ventana en la que pintar
     * 
     * @param paused_ Indica si el juego esta pausado
     */
    void paint(pro2::Window& window, bool paused_) const;

    /**
     * @brief Actualiza el fantsma
     * 
     * @param window Ventana
     */
    void update(pro2::Window& window);

    /**
     * @brief Consigue el rectangulo para la Hitbox
     * 
     * @return pro2::Pt Rectangulo del fantasma
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Devuelve la posicion x 
     * 
     * @return La posicion x
     */
    int get_pos_x() const;

    /**
     * @brief Devuelve la posicion y
     * 
     * @return La posicion y
     */
    int get_pos_y() const;

    /**
     * @brief Devuelve el offset de la x
     * 
     * @return offset de la x
     */
    double get_xoffset() const;

    /**
     * @brief Devuelve el offset de la y
     * 
     * @return offset de la y
     */
    double get_yoffset() const;
private:
    /**
     * @brief Sprite del Fantasma
     * 
     */
    static const std::vector<std::vector<int>> sprite_fantasma;
};


#endif 