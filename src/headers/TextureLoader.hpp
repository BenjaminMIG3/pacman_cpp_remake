#pragma once
#include "config.hpp"


namespace GameEngine{

    class TextureLoader {

        public :
            static SDL_Texture* getPlayerTexture(const char* pathfile);
            static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
            static void deleteTexture(SDL_Texture* texture);
    };

}