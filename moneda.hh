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
    int xoffset_;
    bool encima_;

public:
    Moneda(Pt pos);

    void paint(pro2::Window & window) const;

    void update();


    bool chocan (Mario& mario) const;
    
private:
    static const vector<vector<int>> sprite_moneda;
};



#endif