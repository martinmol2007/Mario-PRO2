#include "game.hh"
#include "assert.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Right, Keys::Left), 
      mario2_({(width / 2) - 30, 150}, 'W', 'D', 'A'),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false), paused_(false) {
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
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
    mario2_.update(window, platforms_);
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
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint(window);
    mario2_.paint(window);
  
    Pt punt = window.camera_center();
    pro2::Rect rect;
    rect.left = punt.x;
    rect.top = punt.y;

    // Parpadea cada x FPS
    if (window.frame_count() % 45 == 0) {
        paint_rect(window, rect, pro2::yellow, 20);
    }

    pro2::Rect r = window.camera_rect();
    paint_square(window, r, pro2::black, 4);

}