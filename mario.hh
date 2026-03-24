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
    Mario(pro2::Pt pos, int j, int r, int l, int contador, int frames) : 
        pos_(pos), 
        last_pos_(pos), 
        jump_key(j), 
        right_key(r), 
        left_key(l), 
        contador_(contador),  
        frames_animacion_(frames) 
    {}

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

    // Apartado Objeto Moneda
    void sumar_moneda() {
        contador_ += 1;
    }

    int contador () const {
        return contador_;
    }

    // Animacion Poner
    void poner_animacion () {
        frames_animacion_ = 60;
        return;
    }

    void actualizar_animacion () {
        if (frames_animacion_ > 0) {
            frames_animacion_--;
        }
        return;
    }

    bool en_animacion () const {
        return (frames_animacion_ > 0 ? true : false);
    }

    // Consigue el sprite dependiendo de si esta en animacion o no
    const std::vector<std::vector<int>> get_sprite () const {
        if (frames_animacion_ > 0) {
            return mario_sprite_moneda_;
        } else {
            return mario_sprite_normal_;
        }
    }

 private:

    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_moneda_;

};

#endif