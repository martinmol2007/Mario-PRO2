#include "game.hh"
#include "assert.hh"

using namespace pro2;
using namespace std;

// Parametros de la ventana 

const int WIDTH = 480, HEIGHT = 320;

// Cantidad de objetos

const int NUMERO_MONEDAS =             5000;
const int NUMERO_FANTASMAS =           5000;
const int NUMERO_PLATAFORMAS =         5000;
const int CANTIDAD_NUBES =            100;
const int CANTIDAD_VIDAS_INICIAL =      5;
const int CANTIDAD_MONEDAS_INICIAL =    10000;
const int CANTIDAD_VIDAS_QUITAR =       1;
const int CANTIDAD_VIDAS_PONER =        1;
const int VALOR_MONEDA =                5;
const int CORAZONES_POR_FILA =          5;
const int SEPARACION_X_COR =           15;
const int SEPARACION_Y_COR =           20;
const int SEPARACION_X_MONEDA =         7;
const int SEPARACION_Y_MONEDA =         0;
const int ELEVEACION_MINI_MONEDA =      5;
const int OFFSET_CORAZONES =           25;
const int OFFSET_MONEDAS =             25;


Game::Game(int width, int height) : 
    mario_({width / 2, 150}, Keys::Space, 'D', 'A', 0, 0), // Controles Mas Comodos
    platforms_ {
        Platform(100, 300, 200, 211),
        Platform(0, 200, 250, 261),
        Platform(250, 400, 150, 161),
    },
    monedas_ {
        new Moneda ({325, 150}), // Moneda de la derecha del todo
        new Moneda ({200, 200}),
        new Moneda ({100, 250}),
    },
    finished_(false), paused_(false) {
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < NUMERO_PLATAFORMAS; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
    for (int i = 0; i < NUMERO_MONEDAS; i++) {
        monedas_.insert(new Moneda({530 + 200*i, 150}));
    }
    for (int i = 0; i < NUMERO_FANTASMAS; i++) {
        fantasmas_.insert(new Fantasma({530 + 200*i, 161}));
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

// Para probar cosas
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
        vidas_ += CANTIDAD_VIDAS_PONER;
        cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
    }
    if(window.was_key_pressed('-') && not paused_) {
        vidas_ -= CANTIDAD_VIDAS_QUITAR;
        if(vidas_ <= 0) matar();
        cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
    }
    if(window.was_key_pressed('M') && not paused_) {
        contador_monedas_ += VALOR_MONEDA;
        cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
    }
    if(window.was_key_pressed('N') && not paused_) {
        contador_monedas_ -= VALOR_MONEDA;
        cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
    }

    return;
}

// Con el finder, solo se actulzian los objetos visibles, NO todos
// Actualizar todos, para que no haya desfase
void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);

    // Provoca que se muevan las monedas
    set<const Moneda*> monedas_visibles = fmonedas_.query(window.camera_rect());
    for(const Moneda* m : monedas_visibles) {
        const_cast<Moneda*>(m)->update(window);
        fmonedas_.update(m);
    }
    
    // Provoca que se muevan los fantasmas
    set<const Fantasma*> fantasmas_visibles = ffantasmas_.query(window.camera_rect());
    for (const Fantasma* f : fantasmas_visibles) {
        const_cast<Fantasma*>(f)->update(window);
        ffantasmas_.update(f);
    }

    // Rectangulo del Mario para colisiones
    Rect rect_mario = mario_.get_rect();

    // Consigue los sets actualizados despues de mover los objetos (monedas)
    set<const Moneda*> monedas_colisiones = fmonedas_.query(window.camera_rect());
    for(const Moneda* m : monedas_colisiones) {
        if(is_collision(rect_mario, m->get_rect())) {
            // Suma lo que vale una moneda
            contador_monedas_ += VALOR_MONEDA;

            // Poner animacion al Mario
            mario_.poner_animacion();
            
            // Borra el objeto del Finder y el Set
            fmonedas_.remove(m);
            monedas_.erase(m);

            // Libera memoria
            delete m;
            
            // Para ver si se borran correctamente
            cout << "CONTADOR MONEDAS: " << contador_monedas_ << endl;
            cout << "TAMAÑO DEL SET DE MONEDAS: " << monedas_.size() << endl;
        }
    }

    // Consigue los sets actualizados despues de mover los objetos (fantasmas)
    set<const Fantasma*> fantasmas_colisiones = ffantasmas_.query(window.camera_rect());
    for(const Fantasma* f : fantasmas_colisiones) {
        if(is_collision(rect_mario, f->get_rect())) {
            // Resta las vidas al Mario
            vidas_ -= CANTIDAD_VIDAS_QUITAR;

            // Si llega a menos de 0 vidas, se acaba
            if(vidas_ < 0) matar();

            // Borra el objeto del Finder y el Set
            ffantasmas_.remove(f);
            fantasmas_.erase(f);

            // Libera memoria
            delete f;

            // Para ver si se borran correctamente
            cout << "CONTADOR DE VIDAS: " << vidas_ << endl;
            cout << "TAMAÑO DEL SET DE LOS FANTASMAS: " << fantasmas_.size() << endl;
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
    // Pintar solo lo que esta mas cerca

    // Pinta las nubes
    for(int i = 0; i < CANTIDAD_NUBES; i += 2) {
        paint_sprite(window, {50*i + 50, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 45, 50 }, sprite_nube, false);
        paint_sprite(window, { 50*i + 48, 47 }, sprite_nube, false);
    }
    
    
    // Pinta los fantasmas
    set<const Fantasma*> f_query = ffantasmas_.query(window.camera_rect());
    for(const Fantasma* f : f_query) {
        f->paint(window, paused_);
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


    // Pinta los contadores visuales de los Corazones (Vidas) y Monedas
    contador_vidas_visual(window);
    contador_monedas_visual(window);


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
    monedas_ = {new Moneda ({325, 150}), new Moneda ({200, 200}), new Moneda ({100, 250})};

    for (int i = 1; i < NUMERO_PLATAFORMAS; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }

    for (int i = 0; i < NUMERO_MONEDAS; i++) {
        monedas_.insert(new Moneda({530 + 200*i, 150}));
    }

    for (int i = 0; i < NUMERO_FANTASMAS; i++) {
        fantasmas_.insert(new Fantasma({530 + 200*i, 161}));
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

void Game::contador_monedas_visual(pro2::Window& window) const {
    // Consigue el reactangulo de la camara
    Rect r = window.camera_rect();

    // Inicializa la posicion de los corazones
    Pt pos_ini_moneda = {r.right - OFFSET_MONEDAS, r.top + OFFSET_MONEDAS};

    // Convierte el valor de monedas en un string para poder recorrelo
    string numero = to_string(contador_monedas_);

    // Para la separacion
    int veces = 0; 

    // Bucle para imprimir el numero de monedas
    for(int i = numero.size()-1; i >= 0; i--) {
        paint_sprite(window, {pos_ini_moneda.x - veces * SEPARACION_X_MONEDA, pos_ini_moneda.y}, selector_sprite_numero((numero[i]) - '0'), false);
        veces += 1;
    }
    // Pinta el simbolo de la moneda
    paint_sprite(window, {pos_ini_moneda.x - veces * (SEPARACION_X_MONEDA + 1) - 5, pos_ini_moneda.y - 1}, sprite_mini_moneda, false);

    return;
}

void Game::contador_vidas_visual(pro2::Window& window) const {
    // Consigue el reactangulo de la camara
    Rect r = window.camera_rect();

    // Inicializa la posicion de los corazones
    Pt pos_ini_cor = {r.left + OFFSET_CORAZONES, r.top + OFFSET_CORAZONES};

    // Bucle para imprimir los corazones
    for(int i = 0; i < vidas_; i++) {
        // Mira la fila y columna en la que va (5 por fila)
        int fila = i / CORAZONES_POR_FILA;
        int columna = i % CORAZONES_POR_FILA;

        // Pinta los corzones
        paint_sprite(window, {pos_ini_cor.x + columna * SEPARACION_X_COR, pos_ini_cor.y + fila * SEPARACION_Y_COR}, sprite_corazon, false);
    }
    
    return;
}