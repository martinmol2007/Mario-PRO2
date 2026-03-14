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

    Pt pos_;
    int contador_;
    bool encima_ = false;

    static const vector<vector<int>> sprite_moneda;

    public:

    Moneda(Pt posicion) : pos_(posicion) {}

    void paint(Window& window) const;

    Pt posicion () const {
        return pos_;
    }

    bool esta_encima () const;

    void encima ();



};



#endif