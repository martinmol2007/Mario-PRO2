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
    bool encima_ = false;

public:
    Moneda(Pt pos);

    void paint(pro2::Window & window) const;

    bool esta_encima () const;
    
    void encima ();
    
    Pt posicion () const {
        return pos_;
    }

    bool chocan (Mario& mario) const;
    
private:
    static const vector<vector<int>> sprite_moneda;
};



#endif