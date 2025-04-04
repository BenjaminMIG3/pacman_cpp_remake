#pragma once
#include "config.hpp"

namespace GameEngine {

    class Pacman;
    class Map;
    class CollisionSystem;
    class Acceuil;
    class GameOver;
    class Blinky;
    class Pinky;
    class Inky;

    class WindowManager {

        enum direction {
            NONE = -1,
            LEFT = 0,
            RIGHT = 1,
            UP = 2,
            DOWN = 3
        };

        enum state {
            ACCEUIL = 0,
            JEU = 1,
            GAME_OVER = 2,
            U_WIN = 3
        };

        enum MapEtat {
            IDLE = 0,
            CHASING = 1
        };

        public:
            //Constructeur de la classe
            WindowManager();
            ~WindowManager(); 
            void show();
            void handleEvents();
            void update();
            void render();

            static SDL_Renderer *renderer;
            static Map* map;
            static CollisionSystem* collisionSystem;

        private:

        const int SCREEN_WIDTH = 480;
        const int SCREEN_HEIGHT = 600;
        const char* title = "My 2D game";

        SDL_Window *window;
        bool quit = false;

        const int FPS = 120;
        const int frameDelay = 1000/FPS;
        Uint32 frameStart;
        int frameTime;

        int etat;

        Pacman* pacman;

        Blinky* blinky;

        Pinky* pinky;

        Inky* inky;

        Acceuil* acceuil;

        GameOver* gameOver;

        //const uint32_t startChasingTimeDuration = 1000;

        FontsLoader* fontsWindowManager;

        SDL_Rect fontRect = {120, 540, 250, 50};
    };  

}

