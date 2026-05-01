#include "moneda.hh"
#include "utils.hh"
#include "window.hh"

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
const int g = 0xd8d8c8;
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
    {_, _, _, y, y, y, y, y, y, _, _, _},
    {_, _, y, y, y, y, y, y, y, y, _, _},
    {_, y, y, g, g, g, g, g, g, y, y, _},
    {y, y, g, g, h, h, g, g, g, g, y, y},
    {y, g, g, h, g, h, g, g, g, g, g, y},
    {y, g, g, g, g, h, g, g, g, g, g, y},
    {y, g, g, g, g, h, g, g, g, g, g, y},
    {y, g, g, g, g, h, g, g, h, h, g, y},
    {y, g, g, g, g, h, g, g, h, g, g, y},
    {y, g, g, g, g, h, g, g, h, h, g, y},
    {y, g, g, g, h, h, h, g, g, g, g, y},
    {y, y, g, g, g, g, g, g, g, g, y, y},
    {_, y, y, g, g, g, g, g, g, y, y, _},
    {_, _, y, y, y, y, y, y, y, y, _, _},
    {_, _, _, y, y, y, y, y, y, _, _, _},
};

// clang-format on


Moneda::Moneda(Pt pos) {
    pos_ = pos;
    xoffset_ = 0.0;
}


// Indica la direccion en que se mueve la moneda
// Esto hace que la moneda se mueva de izquerda a derecha en una zona de (-45, 45) pixeles
// Lo pongo double para que pueda ir con mas precision / decimales
static double direccion = 0.75;

void Moneda::update(pro2::Window& window) {
    // Movimiento horizontal (eje x)
    xoffset_ += direccion;;
    if (xoffset_ > 45) {
        direccion = -0.75;
    }
    else if (xoffset_ < -45) {
        direccion = 0.75;
    }
}


/**
 * @brief Pinta la moneda (xoffset)
 *
 * @param window Ventana en la que pintar
 */
void Moneda::paint(pro2::Window& window) const {
    pro2::Pt p = { int(pos_.x + xoffset_), pos_.y };
    const Pt punto = {p.x - width, p.y - height};
    paint_sprite(window, punto, sprite_moneda, false);
}


pro2::Rect Moneda::get_rect() const {
    pro2::Rect r;
    
    r.left = pos_.x + int(xoffset_) - width/2;
    r.right = pos_.x + int(xoffset_) + width/2;
    r.bottom = pos_.y;
    r.top = pos_.y - height; 

    return r;
}

int Moneda::get_pos_x() const {
    return pos_.x;
}

int Moneda::get_pos_y() const {
    return pos_.y;
}

double Moneda::get_xoffset() const {
    return xoffset_;
}

