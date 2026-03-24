#ifndef MARIO_HH
#define MARIO_HH

// INFO DE MARIO

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    int jump_key, right_key, left_key;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    int contador_;

    std::vector<std::vector<int>> sprite;

    bool en_animacion_;
    int frames_animacion_;

	
 public:
    Mario(pro2::Pt pos, int j, int r, int l, int contador, bool en_animacion, int frames) : pos_(pos), last_pos_(pos), jump_key(j), right_key(r), left_key(l), contador_(contador), en_animacion_(en_animacion), frames_animacion_(frames) {}

    void paint(pro2::Window& window, const std::vector<std::vector<int>>& sprite) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    // Apartado Objeto Monead
    void sumar_moneda() {
        contador_ += 1;
    }

    int contador () const {
        return contador_;
    }

    // Animacion
    void poner_animacion () {
        en_animacion_ = not en_animacion_;
        return;
    }

    bool en_animacion () const {
        return en_animacion_;
    }

    int frames_animacion () const {
        return frames_animacion_;
    }

    void set_frames_animacion () {
        frames_animacion_ = 1000;
        return; 
    }

    void restar_frames_animacion () {
        if (frames_animacion_ >= 0) frames_animacion_--;
        return;
    }

    // Consigue el sprite dependiendo de si esta en animacion o no
    std::vector<std::vector<int>> get_sprite () {
        if (frames_animacion_ > 0) {
            return mario_sprite_moneda_;
        } else {
            return mario_sprite_normal_;
        }
    }

    // Pone el sprite dependiendo de si esta o no (otra funcion)
    void set_sprite () {
        sprite = get_sprite();
        return;
    }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    
    static const std::vector<std::vector<int>> mario_sprite_moneda_;
};

#endif