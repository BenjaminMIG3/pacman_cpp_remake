#include "headers/FontsLoader.hpp"

namespace GameEngine {

    FontsLoader::FontsLoader(const char *text, int taille, SDL_Rect rect){
        if(TTF_WasInit() == 0) {
            if (TTF_Init() == 0) {
                std::cout << "Initialisation de SDL TTF réussie" << std::endl;
            } else {
                std::cerr << "Erreur lors de l'initialisation de SDL TTF : " << TTF_GetError() << std::endl;
            }
        } else {
            std::cout << "TTD déja initialisé" << std::endl;
        }
        

        this->fontColor = { 255, 255, 255, 255 };
        this->fontSize = taille;
        this->fontRect = rect;

        this->font = TTF_OpenFont("assets/fonts/atari.ttf", fontSize);

        if (!font) {
            std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
        }

        this->message = text;

        this->fontSurface = TTF_RenderText_Solid(this->font, this->message, this->fontColor);

        this->fontTexture = SDL_CreateTextureFromSurface(WindowManager::renderer, this->fontSurface);

        if (!this->fontTexture) {
            std::cerr << "Erreur lors de la création de la texture : " << SDL_GetError() << std::endl;
            // Gestion de l'erreur
        }

        SDL_FreeSurface(this->fontSurface);

    }

    /**
     * Procédure qui mets à jour le texte à affichier
     */
    void FontsLoader::setMessage(const char* texte) {
        if(texte == nullptr) {
            throw std::runtime_error("Adresse de texte null");
        }

        this->message = texte;

        this->fontSurface = TTF_RenderText_Solid(this->font, this->message, this->fontColor);
        if(this->fontSurface == nullptr) {
            std::cerr << "Erreur lors de la création de la surface de texte : " << TTF_GetError() << std::endl;
            throw std::runtime_error("FontSurface pointeur is null");
        }

        this->fontTexture = SDL_CreateTextureFromSurface(WindowManager::renderer, this->fontSurface);
        if (!this->fontTexture) {
            std::cerr << "Erreur lors de la création de la texture : " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(this->fontSurface); // Libération de la surface une fois la texture créée
    }

    void FontsLoader::setPosToText(int posX, int posY) {
        this->fontRect.x = posX;
        this->fontRect.y = posY;
    }

    void FontsLoader::destroyFont(TTF_Font* font) {
        TTF_CloseFont(font);
    }

    FontsLoader::~FontsLoader(){
        if(TTF_WasInit()) {
            this->destroyExistentFonts();
        }
    }

    void FontsLoader::destroyExistentFonts(){
        TTF_CloseFont(this->font);
    }

    void FontsLoader::drawFont() {
        SDL_RenderCopy(WindowManager::renderer, this->fontTexture, NULL, &this->fontRect);
    }

}