#ifndef UTILS_HH
#define UTILS_HH

#include <vector>

#include "geometry.hh"
#include "window.hh"

#include "mario.hh"
#include "moneda.hh"

namespace pro2 {

/**
 * @brief Dibuixa una línia horitzontal a la finestra.
 *
 * @param window Finestra a la qual es dibuixa la línia.
 * @param xini Coordenada x inicial.
 * @param xfin Coordenada x final.
 * @param y Coordenada y.
 * @param color Color de la línia (opcional, si no es posa s'assumeix `white`).
 */
void paint_hline(pro2::Window& window, int xini, int xfin, int y, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa una línia vertical a la finestra.
 *
 * @param window Finestra a la qual es dibuixa la línia.
 * @param x Coordenada x.
 * @param yini Coordenada y inicial.
 * @param yfin Coordenada y final.
 * @param color Color de la línia (opcional, si no es posa s'assumeix `white`).
 */
void paint_vline(pro2::Window& window, int x, int yini, int yfin, pro2::Color color = pro2::white);

/** 
* @brief  Dibuixa el marc del color indicat
* 
* @param window Finestra
* @param r Rectangle (coordenades)
* @param color Color
* @param mida Mida
*/
void paint_square(pro2::Window& window, pro2::Rect& r, pro2::Color color, int mida);


/**
 * @brief 
 * 
 * @param window Ventana
 * @param r Tipo Rectangulo
 * @param color Color
 * @param mida Mida del Rectangle
 */
void paint_rect(pro2::Window& window, pro2::Rect& r, pro2::Color color, int mida);

/**
 * @brief Dibuixa una imatge/textura a la finestra a partir d'una posició
 *
 * @param window Finestra a la que pintar
 * @param orig   Origen (cantonada de dalt a l'esquerra) del rectangle que forma el _sprite_
 * @param sprite Matriu de colors que representa la imatge (_sprite_).
 * @param mirror Si cal pintar girar la textura horitzontalment
 */
void paint_sprite(pro2::Window& window, pro2::Pt orig, const std::vector<std::vector<int>>& sprite, bool mirror);

/**
 * @brief Devuelve si hay colision entre la moneda y el mario
 * 
 * @param mario Mario
 * @param moneda Moneda
 * @return true Si hay colision
 * @return false Si no hay colision
 */
bool hay_colision (const Mario& mario, const Moneda& moneda);

/**
 * @brief Mira si hay colision en la hitbox del Mario y la Moneda
 * 
 * @param a Hitbox del Mario
 * @param b Hitbox de la Moneda
 * @return true Si pasa cerca
 * @return false Si no pasan cerca
 */
bool is_collision (const pro2::Rect& a, const pro2::Rect& b);

}  // namespace pro2

#endif