#pragma once
#include "config.hpp"

namespace GameEngine {
    
    class FontsLoader;

    class Acceuil {

        public: 

            Acceuil();

            void draw();

        private:

            SDL_Texture* logoPacman;

            SDL_Rect fontRect = {145, 300, 200, 20}; 

            SDL_Rect srcR, destR;

            FontsLoader* fontsLoader;

    };
}