#include <vector>
#include "window.hh"

using namespace std;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;
const int o = pro2::white; // Blanco


/**
 * @brief Nube estilo pixel art
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