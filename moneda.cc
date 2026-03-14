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

/**
 * @brief Estilo pixel art de la moneda de Mario Bros
 * 
 */
const vector<vector<int>> Moneda::sprite_moneda = {
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, h, h, h, h, h, h, _, _, _},
    {_, _, h, h, s, s, s, h, s, h, _, _},
    {_, h, s, h, h, s, s, s, h, s, h, _},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, h, h, s, s, s, s, s, s, s, h, _},
    {_, h, h, h, h, r, h, h, h, h, h, _},
    {_, h, r, r, h, h, r, b, h, r, h, _},
    {_, h, r, r, b, b, b, b, h, r, h, _},
    {_, h, h, b, y, b, b, y, b, r, h, _},
    {_, h, h, b, b, b, b, b, b, g, h, _},
    {_, _, h, b, b, b, b, b, b, h, _, _},
    {_, _, _, h, h, h, h, h, h, _, _, _},
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

    const Pt punto = {posicion().x - 6, posicion().y - 15 };
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