#ifndef GAME_HH
#define GAME_HH

#include "mario.hh"
#include "moneda.hh"
#include "fantasma.hh"
#include "nube.hh"
#include "platform.hh"

#include "window.hh"
#include "utils.hh"
#include "finder.hh"

#include <vector>
#include <list>
#include <iostream>

class Game {
    Mario mario_;

    Finder<Platform> fplatforms_;
    Finder<Moneda> fmonedas_;
    Finder<Fantasma> ffantasmas_;

    std::vector<Platform> platforms_;
    std::list<Moneda> monedas_;
    std::list<Fantasma> fantasmas_;

    int contador_monedas_;
    int vidas_;

    bool finished_;
    bool paused_;
    bool muerto_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

    void reset(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif