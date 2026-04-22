#include "moneda.hh"
#include "utils.hh"
#include "window.hh"

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using namespace pro2;

// Variables globales para los sprites

const int width = 6;
const int height = 15;

// Paleta de Colores para moneda

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;
const int v = pro2::green;
const int a = 0x0a6fb6;  // azul oscuro
const int c = 0x6ec6e8;  // azul claro
const int d = 0xbfefff;  // brillo

// clang-format off

/**
 * @brief Moneda estilo pixel art
 */
const vector<vector<int>> Moneda::sprite_moneda = {
    {_, _, _, _, _, _, _, _, _, _, _, _}, 
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
};

// clang-format on


Moneda::Moneda(Pt pos) {
    pos_ = pos;
    xoffset_ = 0;
}


bool Moneda::chocan(Mario& mario) const {
    Pt p = { pos_.x + xoffset_, pos_.y };
    return (abs(p.x - mario.pos().x) <= 5) && (abs(p.y - mario.pos().y) <= 5);
}


// Indica la direccion en que se mueve la moneda
// Esto hace que la moneda se mueva de izquerda a derecha en una zona de (-45, 45) pixeles
int direccion = 1;

void Moneda::update() {
    xoffset_ += direccion;;
    if (xoffset_ > 45) {
        direccion = -1;
    }
    else if (xoffset_ < -45) {
        direccion = 1;
    }
}


/**
 * @brief Pinta la moneda (xoffset)
 *
 * @param window Ventana en la que pintar
 */
void Moneda::paint(pro2::Window& window) const {
    Pt p = { pos_.x + xoffset_, pos_.y };
    const Pt punto = {p.x - width, p.y - height};
    paint_sprite(window, punto, sprite_moneda, false);
}


pro2::Rect Moneda::get_rect () const {
    pro2::Rect r;
    
    r.left = pos_.x - width/2;
    r.right = pos_.x + width/2;
    r.bottom = pos_.y;
    r.top = pos_.y - height; 

    return r;
}