#include "moneda.hh"
#include "window.hh"
#include "mario.hh"
#include "utils.hh"

#include <iostream>
#include <vector>


using namespace std;
using namespace pro2;


const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;
const int v = pro2::green;

const int a = 0x0a6fb6;     // azul oscuro
const int c = 0x6ec6e8;     // azul claro
const int d = 0xbfefff;     // brillo


/**
 * @brief Esmeralda estilo pixel art
 */
const vector<vector<int>> Moneda::sprite_moneda = {
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, h, h, _, _, _, _, _},
    {_, _, _, _, h, c, c, h, _, _, _, _},
    {_, _, _, h, c, d, d, c, h, _, _, _},
    {_, _, h, c, c, c, c, c, c, h, _, _},
    {_, h, c, c, b, c, c, b, c, c, h, _},
    {_, h, c, b, b, b, b, b, b, c, h, _},
    {_, h, b, b, b, c, c, b, b, b, h, _},
    {_, h, b, b, c, c, c, c, b, b, h, _},
    {_, _, h, c, b, b, b, b, c, h, _, _},
    {_, _, _, h, c, b, b, c, h, _, _, _},
    {_, _, _, _, h, b, b, h, _, _, _, _},
    {_, _, _, _, _, h, h, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
};


/**
 * @brief Pinta la moneda
 * 
 * @param window Ventana en la que pintar
 */
void Moneda::paint(pro2::Window& window) const {
    if (encima_) return;

    const Pt punto = {pos_.x - 6, pos_.y - 15 - 1};
    paint_sprite(window, punto, sprite_moneda, false);

}

/**
 * @brief Construct a new Moneda:: Moneda object
 * 
 * @param pos Pos en la que se construye
 */
Moneda::Moneda(Pt pos) {
    pos_ = pos;
}


/**
 * @brief Mira si esta esta encima de la moneda para cogerla
 * 
 */
bool Moneda::esta_encima() const {
    return encima_;
}

/**
 * @brief Si pasa por encima (de la moneda), lo pone a true
 * 
 */
void Moneda::encima() {
    encima_ = true;
}

void Moneda::update(Mario& mario, Moneda& moneda) {
    pro2::Pt punto = moneda.pos_;
    if (punto.x == mario.pos().x && punto.y == mario.pos().y) { // Faltaria poner que la coja cuando este cerca
        moneda.encima_ = true;
        mario.sumar_moneda();
    }
}
