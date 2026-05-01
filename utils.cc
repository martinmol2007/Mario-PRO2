// TODO LO QUE TIENE QUE VER CON PAINT (PINTAR)

#include "utils.hh"
#include "assert.hh"

using namespace std;

namespace pro2 {

void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    assert(xini <= xfin, "Els limits de la linia horitzontal no son valids.");
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    assert(yini <= yfin, "Els limits de la linia vertical no son valids.");
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}


void paint_rect(pro2::Window& window, pro2::Rect& r, pro2::Color color, int mida) {
    for (int i = 0; i < mida; i++) {
        paint_hline(window, r.left, r.left+50, r.top-i, color);
        paint_hline(window, r.left-50, r.left, r.top-i, color);
    }
}

void paint_square(pro2::Window& window, pro2::Rect& r, pro2::Color color, int mida) {
    for (int i = 0; i < mida; i++) {
        paint_hline(window, r.left, r.right, r.top+i, color);
        paint_hline(window, r.left, r.right, r.bottom-i-1, color);
        paint_vline(window, r.left+i, r.top, r.bottom, color);
        paint_vline(window, r.right-1-i, r.top, r.bottom, color);
    }
}

void paint_sprite(pro2::Window& window, pro2::Pt orig, const vector<vector<int>>& sprite, bool mirror) {
    assert(!sprite.empty(), "L'sprite no pot ser buit.");
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

/*
bool hay_colision(const Mario& mario, const Moneda& moneda) {
    // Pt p = { moneda.get_pos_x() + moneda.get_xoffset(), moneda.get_pos_y() };
    // return (abs(p.x - mario.pos().x) <= 5) && (abs(p.y - mario.pos().y) <= 5);
    return is_collision(mario.get_rect(), moneda.get_rect());
}
*/

// Actua como hitbox para ver si Mario y Moneda colisionan
// Si el rectangulo B esta sobre el rectangulo A, han chocado
bool is_collision(const pro2::Rect& a, const pro2::Rect& b) {
    if (a.top <= b.top && b.top <= a.bottom) {
        if (a.left <= b.left && b.left <= a.right) return true;
        if (a.left <= b.right && b.right <= a.right) return true;
    }
    else if (a.top <= b.bottom && b.bottom <= a.bottom) {
        if (a.left <= b.left && b.left <= a.right) return true;
        if (a.left <= b.right && b.right <= a.right) return true;
    }
    return false;
}

}  // namespace pro2