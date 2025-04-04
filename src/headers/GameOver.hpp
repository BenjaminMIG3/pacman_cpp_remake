#pragma once
#include "config.hpp"

namespace GameEngine {

    class FontsLoader;

    class GameOver {
        public: 

            GameOver();

            void draw();

        private:

            SDL_Texture* ripTexture;

            SDL_Rect fontRect = {145, 350, 200, 20}; 

            SDL_Rect srcR, destR;

            FontsLoader* fontsLoader;
    };
}