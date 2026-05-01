#include "fantasma.hh"

using namespace std;
using namespace pro2;

// Direccion para el movimiento horizontal

double direccion = 0.5;

// Variables globales para los sprites

const int width = 6;
const int height = 15;

// Paleta de Colores para moneda

const int _ = -1;
const int h = pro2::white;
const int o = pro2::black;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int g = 0xd8d8c8;
const int w = 0x8d573c;
const int v = pro2::green;
const int a = 0x0a6fb6;  // azul oscuro
const int c = 0x6ec6e8;  // azul claro
const int d = 0xbfefff;  // brillo

const vector<vector<int>> Fantasma::sprite_fantasma = {
    {_, _, _, _, h, h, h, h, _, _, _, _},
    {_, _, _, h, h, h, h, h, h, _, _, _},
    {_, _, h, h, h, h, h, h, h, h, _, _},
    {_, h, h, h, h, h, h, h, h, h, h, _},
    {h, h, h, h, h, h, h, h, h, h, h, h},
    {h, h, h, _, h, h, _, h, h, h, h, h},
    {h, h, h, _, h, h, _, h, h, h, h, h},
    {h, h, h, h, h, _, h, h, h, h, h, h},
    {h, h, h, h, h, h, h, h, h, h, h, h},
    {h, h, h, h, h, h, h, h, h, h, h, h},
    {h, h, h, h, h, h, h, h, h, h, h, h},
    {h, h, h, h, h, h, h, h, h, h, h, h},
    {_, h, h, h, h, h, h, h, h, h, h, _},
    {_, _, h, _, h, _, h, _, h, _, _, _},
    {_, _, _, h, _, h, _, h, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
};

Fantasma::Fantasma(Pt pos) {
    pos_ = { pos.x , pos.y };
    xoffset_ = 0.0;
    yoffset_ = 0.0;
}


void Fantasma::update(Window& window) {
    // Movimiento horizontal (eje x)
    xoffset_ += direccion;;
    if (xoffset_ > 30) {
        direccion = -0.5;
    }
    else if (xoffset_ < -30) {
        direccion = 0.5;
    }

    // Movimiento vertical (eje y)
    yoffset_ = 3 * sin(0.125 * window.frame_count());
}

void Fantasma::paint(Window& window) const {
    Pt p = { int(pos_.x + xoffset_), pos_.y };
    const Pt punto = {p.x - width, p.y - height};

    if (window.frame_count() % 15 == 0) {
        bool mirror = direccion > 0 ? true : false;
        paint_sprite(window, punto, sprite_fantasma, mirror);
    }
}

Rect Fantasma::get_rect() const {
    pro2::Rect r;
    
    r.left = pos_.x + int(xoffset_) - width/2;
    r.right = pos_.x + int(xoffset_) + width/2;
    r.bottom = pos_.y + int(yoffset_);
    r.top = pos_.y - height; 

    return r;
}

int Fantasma::get_pos_x() const {
    return pos_.x;
}

int Fantasma::get_pos_y() const {
    return pos_.y;
}

double Fantasma::get_xoffset() const {
    return xoffset_;
}

double Fantasma::get_yoffset() const {
    return yoffset_;
}
