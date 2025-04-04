#pragma once 
#include "config.hpp"

namespace GameEngine {
    class FontsLoader {

        public :

            FontsLoader(const char *text, int size, SDL_Rect rect);
            ~FontsLoader();

            // Détruit une police chargée
            static void destroyFont(TTF_Font* font);

            void drawFont();

            void setPosToText(int posX, int posY);
            
            void setMessage(const char *message);
            
        private : 

            const char *message;

            int fontSize;

            SDL_Rect fontRect;

            TTF_Font* font;

            SDL_Color fontColor;

            SDL_Surface* fontSurface;

            SDL_Texture* fontTexture;

            void destroyExistentFonts();

    };
}