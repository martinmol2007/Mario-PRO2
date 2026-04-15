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
    moneda_ {
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
        moneda_.push_back(Moneda({530 + 200*i, 150}));
    }
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
    mario_.update(window, platforms_);
    
    for (int i = 0; i < moneda_.size(); i++) {
        // TODO: Si el mario i al moneda intersecten, esborro la moneda del vector
        vector<Moneda>::const_iterator it = &moneda_[i];
        
        if (moneda_[i].chocan(mario_)) {
            mario_.sumar_moneda();
            mario_.poner_animacion();
            moneda_.erase(it);
        }
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
    // cout << mario_.contador() << endl;
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);

    for (const Platform& p : platforms_) {
        p.paint(window);
    }

    // Imprime las monedas
    for (const Moneda& m : moneda_) {
        m.paint(window);
    }

    mario_.paint(window, mario_.get_sprite());
    
    // Pintar el marco negro
    Rect r = window.camera_rect();
    paint_square(window, r, black, 4);

    // Poner un sol
    // paint_sprite(window);

}