#include "game.hh"
#include "assert.hh"

using namespace pro2;

Game::Game(int width, int height) : 
    mario_({width / 2, 150}, Keys::Space, 'D', 'A', 0, 0), // Controles Mas Comodos
    platforms_ {
        Platform(100, 300, 200, 211),
        Platform(0, 200, 250, 261),
        Platform(250, 400, 150, 161),
    },
    monedas_ {
        Moneda ({325, 150}), // Moneda de la derecha del todo
        Moneda ({200, 200}),
        Moneda ({100, 250}),
    },
    finished_(false), paused_(false) {
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }

    for (int i = 0; i < 20; i++) {
        monedas_.push_back(Moneda({530 + 200*i, 150}));
    }
    // Las monedas las lleva el Juego
    contador_monedas_ = 0;
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if(window.was_key_pressed('P')) {
        paused_ = not paused_;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    if (not paused_) {
        mario_.update(window, platforms_);
        
        // Provoca que se muevan las monedas
        for (Moneda& m : monedas_) {
            // Mueve cada moneda (animacion)
            m.update();
        }
        
        // Comprobar si las monedas chocan con Mario (se las recoge)
        auto it = monedas_.begin();
    
        while (it != monedas_.end()) {
            // Lo borras, se avanza solo el iterador
            if (hay_colision(mario_, (*it))) {
                contador_monedas_ += 1;
                mario_.poner_animacion();
                it = monedas_.erase(it);
            }
            // No borras
            else {
                it++;
            }
        }
        // Sacar el tamaño del vector de monedas (para comprobar si se estan eleminado las monedas sobrantes)
        // cout << monedas_.size() << endl;
    }
}


void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();
    
    int dx = pos.x - cam.x;
    int dy = pos.y - cam.y;
    
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if(not paused_) {
        update_objects(window);
        update_camera(window);
    }
    // cout << contador_monedas_ << endl;
}


void Game::paint(pro2::Window& window) {
    // Pinta el cielo color azul
    window.clear(sky_blue);

    // Pinta las nubes
    for (int i = 0; i < 100; i += 2) {
        paint_sprite(window, {50*i + 50, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 45, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 48, 47 }, sprite_nube, false);
    }

    // Pinta las plataformas
    for (const Platform& p : platforms_) {
        p.paint(window);
    }

    // Pinta las monedas
    for (const Moneda& m : monedas_) {
        m.paint(window);
    }

    // Pinta el Mario
    mario_.paint(window, mario_.get_sprite());
    
    // Pintar el marco negro
    Rect r = window.camera_rect();
    paint_square(window, r, black, 4);
}