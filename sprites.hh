#ifndef SPRITES_HH
#define SPRITES_HH

#include <vector>
#include "window.hh"

using namespace std;
using namespace pro2;

// Paleta de Colores

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;
const int o = pro2::white; 

/**
 * @brief Nube estilo pixel art
 * 
 */
const vector<vector<int>> sprite_nube = {
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, o, o, o, o, _, _, _, _},
    {_, _, _, o, o, o, g, g, o, o, _, _},
    {_, _, o, o, o, o, o, o, g, o, _, _},
    {_, _, o, o, o, o, o, o, o, o, o, _},
    {_, _, o, g, o, o, o, o, o, o, o, _},
    {_, _, o, g, o, o, o, o, o, o, o, _},
    {_, _, _, o, g, o, o, o, o, o, _, _},
    {_, _, _, _, o, o, o, o, o, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
};


/**
 * @brief Sprite de mini moneda estilo Pixel art
 * 
 */
const vector<vector<int>> sprite_mini_moneda = {
    {_, _, y, y, y, y, _, _},
    {_, y, y, o, o, y, y, _},
    {y, y, y, y, y, y, y, y},
    {y, o, y, y, y, o, y, y},
    {y, o, y, y, y, o, y, y},
    {y, y, y, y, y, y, y, y},
    {_, y, y, o, o, y, y, _},
    {_, _, y, y, y, y, _, _},
};


const std::vector<std::vector<int>> sprite_corazon = {
    {_, _, _, _, _, _, _, _},
    {_, r, r, _, _, r, r, _},
    {r, r, o, r, r, r, r, r},
    {r, r, r, r, r, r, r, r},
    {_, r, r, r, r, r, r, _},
    {_, _, r, r, r, r, _, _},
    {_, _, _, r, r, _, _, _},
    {_, _, _, _, _, _, _, _},
};


const vector<vector<int>> num_0 = {
    {y, y, y},
    {y, _, y},
    {y, _, y},
    {y, _, y},
    {y, y, y},
};


const vector<vector<int>> num_1 = {
    {_, y, _},
    {y, y, _},
    {_, y, _},
    {_, y, _},
    {y, y, y},
};


const vector<vector<int>> num_2 = {
    {y, y, y},
    {_, _, y},
    {y, y, y},
    {y, _, _},
    {y, y, y},
};


const vector<vector<int>> num_3 = {
    {y, y, y},
    {_, _, y},
    {y, y, y},
    {_, _, y},
    {y, y, y},
};


const vector<vector<int>> num_4 = {
    {y, _, y},
    {y, _, y},
    {y, y, y},
    {_, _, y},
    {_, _, y},
};


const vector<vector<int>> num_5 = {
    {y, y, y},
    {y, _, _},
    {y, y, y},
    {_, _, y},
    {y, y, y},
};


const vector<vector<int>> num_6 = {
    {y, y, y},
    {y, _, _},
    {y, y, y},
    {y, _, y},
    {y, y, y},
};


const vector<vector<int>> num_7 = {
    {y, y, y},
    {_, _, y},
    {_, y, _},
    {y, _, _},
    {y, _, _},
};


const vector<vector<int>> num_8 = {
    {y, y, y},
    {y, _, y},
    {y, y, y},
    {y, _, y},
    {y, y, y},
};


const vector<vector<int>> num_9 = {
    {y, y, y},
    {y, _, y},
    {y, y, y},
    {_, _, y},
    {y, y, y},
};


#endif