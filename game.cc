#include "game.hh"
#include "assert.hh"

// Parametros de la ventana 

const int WIDTH = 480, HEIGHT = 320;

// Cantidad de objetos

const int NUMERO_MONEDAS =           1000000;
const int NUMERO_FANTASMAS =         1000000;
const int NUMERO_PLATAFORMAS =       1000000;
const int CANTIDAD_NUBES =            100;
const int CANTIDAD_VIDAS_INICIAL =     15;
const int CANTIDAD_MONEDAS_INICIAL =    0;
const int CANTIDAD_VIDAS_QUITAR =       1;

const int VALOR_MONEDA = 1;

using namespace pro2;
using namespace std;

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
    for (int i = 1; i < NUMERO_PLATAFORMAS; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
    for (int i = 0; i < NUMERO_MONEDAS; i++) {
        monedas_.push_back(Moneda({530 + 200*i, 150}));
    }
    for (int i = 0; i < NUMERO_FANTASMAS; i++) {
        fantasmas_.push_back(Fantasma({530 + 200*i, 161}));
    }

    // Inicializa los finders
    finder_inicializar(fmonedas_, monedas_);
    finder_inicializar(ffantasmas_, fantasmas_);
    finder_inicializar(fplatforms_, platforms_);

    
    // Atributos "del" Mario que los lleva el juego
    contador_monedas_ = CANTIDAD_MONEDAS_INICIAL;
    vidas_ = CANTIDAD_VIDAS_INICIAL;
    muerto_ = false;
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
    if(window.was_key_pressed('R') && muerto_) {
        reset(window);
        update_camera(window);
        return;
    }
    if(window.was_key_pressed('K')) {
        reset(window);
        update_camera(window);
        return;
    }
    if(window.was_key_pressed('H') && not paused_) {
        vidas_ += 1;
        cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
    }
    if(window.was_key_pressed('M') && not paused_) {
        contador_monedas_ += 1;
        cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
    }
}

// Con el finder, solo se actulzian los objetos visibles, NO todos
// Actualizar todos, para que no haya desfase

// Preguntar si se tienen que mover todas o las que estan visbles
void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    

    // Provoca que se muevan las monedas
    set<const Moneda*> monedas_visibles = fmonedas_.query(window.camera_rect());
    for(const Moneda* m : monedas_visibles) {
        //m.update(window);
        const_cast<Moneda*>(m)->update(window);
        fmonedas_.update(m);
    }
    
    // Provoca que se muevan los fantasmas
    set<const Fantasma*> fantasmas_visibles = ffantasmas_.query(window.camera_rect());
    for (const Fantasma* f : fantasmas_visibles) {
        const_cast<Fantasma*>(f)->update(window);
        // f.update(window);
        ffantasmas_.update(f);
    }
    
    // Comprobar si las monedas chocan con Mario (se las recoge)
    // auto it_m = monedas_.begin();

    // Rectangulo del Mario para colisiones
    Rect rect_mario = mario_.get_rect();

    // Consigue los sets actualizados despues de mover los objetos (monedas)
    set<const Moneda*> monedas_colisiones = fmonedas_.query(window.camera_rect());
    
    for(const Moneda* m : monedas_colisiones) {
        if(is_collision(rect_mario, m->get_rect())) {
            contador_monedas_ += VALOR_MONEDA;

            mario_.poner_animacion();
            
            fmonedas_.remove(m);
            
            bool trobat = false;
            for(auto it = monedas_.begin(); it != monedas_.end() && not trobat; it++) {
                if((&*it) == m) {
                    trobat = true;
                    monedas_.erase(it);
                }
            }

            cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
            cout << "TAMAÑO DE LA LISTA DE MONEDAS: " << monedas_.size() << endl;
        }
    }

    // Consigue los sets actualizados despues de mover los objetos (fantasmas)
    set<const Fantasma*> fantasmas_colisiones = ffantasmas_.query(window.camera_rect());

    for(const Fantasma* f : fantasmas_colisiones) {
        if(is_collision(rect_mario, f->get_rect())) {
            vidas_ -= CANTIDAD_VIDAS_QUITAR;

            ffantasmas_.remove(f);

            bool trobat = false;
            for(auto it = fantasmas_.begin(); it != fantasmas_.end() && not trobat; it++) {
                if(&(*it) == f) {
                    trobat = true;
                    fantasmas_.erase(it);
                }
            }

            cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
            cout << "TAMAÑO DE LA LISTA DE FANTASMAS: " << fantasmas_.size() << endl;
        }
    }
    
    /*
    while (it_m != monedas_.end()) {
        // Lo borras, se avanza solo el iterador
        if (is_collision(rect_mario, (*it_m).get_rect())) {
            contador_monedas_ += 1;
            mario_.poner_animacion();
            
            // Borra del finder la moneda tras ser recogida
            fmonedas_.remove(&(*it_m));
           
            it_m = monedas_.erase(it_m);

            
            cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
            cout << "TAMAÑO DE LA LISTA DE MONEDAS: " << monedas_.size() << endl;

        }
        // No borras
        else {
            it_m++;
        }
    }
    */

    /*
    // Comprueba si se choca con un fantasma
    auto it_f = fantasmas_.begin();

    while (it_f != fantasmas_.end()) {
        if (is_collision(rect_mario, (*it_f).get_rect())) {
            vidas_ -= CANTIDAD_VIDAS_QUITAR;

            // Borra del finder el fantasma tras ser recogida
            ffantasmas_.remove(&(*it_f));
            
            it_f = fantasmas_.erase(it_f);


            cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
            cout << "TAMAÑO DE LA LISTA DE FANTASMAS: " << fantasmas_.size() << endl;

            if (vidas_ == 0) muerto_ = true;
        } else {
            it_f++;
        }
    }  
    */
        
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
    if(not paused_ and not muerto_) {
        update_objects(window);
        update_camera(window);
    }
}


void Game::paint(pro2::Window& window) {
    // Pinta el cielo color rojo si estas muerto
    if (muerto_) {
        window.clear(red);
        return;
    } 
    
    window.clear(sky_blue);

    // Pintar solo los objetos cercanos, ya que es lo que mas tarda

    // Pinta las nubes
    for (int i = 0; i < CANTIDAD_NUBES; i += 2) {
        paint_sprite(window, {50*i + 50, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 45, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 48, 47 }, sprite_nube, false);
    }

    // Pinta los fantasmas
    set<const Fantasma*> f_query = ffantasmas_.query(window.camera_rect());
    for(const Fantasma* f : f_query) {
        f->paint(window);
    }
    

    // Pinta las plataformas
    set<const Platform*> p_query = fplatforms_.query(window.camera_rect());
    for(const Platform* p : p_query) {
        p->paint(window);
    }
   

    // Pinta las monedas
    set<const Moneda*> m_query = fmonedas_.query(window.camera_rect());
    for(const Moneda* m : m_query) {
        m->paint(window);
    }
    
    
    // Pinta el Mario
    mario_.paint(window, mario_.get_sprite());
    

    // Pintar el marco negro
    Rect r = window.camera_rect();
    paint_square(window, r, black, 4);
}

void Game::reset(pro2::Window& window) {
    mario_ = Mario({WIDTH / 2, 150}, Keys::Space, 'D', 'A', 0, 0);

    platforms_.clear();
    monedas_.clear();
    fantasmas_.clear();

    platforms_ = {Platform(100, 300, 200, 211), Platform(0, 200, 250, 261), Platform(250, 400, 150, 161)};
    monedas_ = {Moneda ({325, 150}), Moneda ({200, 200}), Moneda ({100, 250})};

    for (int i = 1; i < NUMERO_PLATAFORMAS; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }

    for (int i = 0; i < NUMERO_MONEDAS; i++) {
        monedas_.push_back(Moneda({530 + 200*i, 150}));
    }

    for (int i = 0; i < NUMERO_FANTASMAS; i++) {
        fantasmas_.push_back(Fantasma({530 + 200*i, 161}));
    }

    // Vacia todos los finders
    fmonedas_.clear();
    ffantasmas_.clear();
    fplatforms_.clear();

    // Inicializa los finders
    finder_inicializar(fmonedas_, monedas_);
    finder_inicializar(ffantasmas_, fantasmas_);
    finder_inicializar(fplatforms_, platforms_);
   
    contador_monedas_ = CANTIDAD_MONEDAS_INICIAL;
    vidas_ = CANTIDAD_VIDAS_INICIAL;
    muerto_ = false;
    paused_ = true;
}