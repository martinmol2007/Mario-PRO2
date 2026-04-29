#ifndef MARIO_HH
#define MARIO_HH

// INFO DE MARIO

#include <vector>
#include "platform.hh"
#include "window.hh"

using namespace pro2;

class Mario {
 private:
    Pt pos_, last_pos_;
    Pt speed_ = {0, 0};
    Pt accel_ = {0, 0};
    
    int accel_time_ = 0;

    int jump_key, right_key, left_key;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    // Frames de la animacion
    int frames_animacion_ = 0;

    std::vector<std::vector<int>> sprite;
	
 public:
    Mario(pro2::Pt pos, int j, int r, int l, int contador, int frames) : 
        pos_(pos), 
        last_pos_(pos), 
        jump_key(j), 
        right_key(r), 
        left_key(l),   
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

    /**
     * @brief Pone la animacion
     * 
     */
    void poner_animacion () {
        frames_animacion_ += 60;
        return;
    }

    /**
     * @brief Actualiza la animacion
     * 
     */
    void actualizar_animacion () {
        if (frames_animacion_ > 0) {
            frames_animacion_--;
        }
        return;
    }

    /**
     * @brief Devuevle si esta en animacion o no
     * 
     * @return Devuelve true si esta en animacion
     * @return Devuelve false si no esta en animacion
     */
    bool en_animacion () const {
        return (frames_animacion_ > 0 ? true : false);
    }

    /**
     * @brief Get the sprite object
     * 
     * @return Consigue el sprite dependiendo de si esta en animacion
     */
    const std::vector<std::vector<int>> get_sprite () const {
        if (frames_animacion_ > 0) {
            return mario_sprite_moneda_;
        } else {
            return mario_sprite_normal_;
        }
    }

    /**
     * @brief Devuelve el Rectangulo de Mario (hitbox)
     * 
     * @return Rectangulo de la Hitbox de Mario
     */
    pro2::Rect get_rect() const;

 private:
 
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_moneda_;
};

#endif