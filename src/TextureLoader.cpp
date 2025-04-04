#include "headers/TextureLoader.hpp"

namespace GameEngine {

    SDL_Texture* TextureLoader::getPlayerTexture(const char* pathfile){
        SDL_Surface* tmpSurface = IMG_Load(pathfile);
        if (tmpSurface == nullptr) {
            std::cout << "Erreur lors du chargement de l'image : " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* tex = SDL_CreateTextureFromSurface(WindowManager::renderer, tmpSurface);
        if (tex == nullptr) {
            std::cout << "Erreur lors de la création de la texture : " << SDL_GetError() << std::endl;
        }
        else {
            std::cout << "Création de la texure réussie ! path : " << pathfile << std::endl;
        }

        SDL_FreeSurface(tmpSurface);
        return tex;
    }

    void TextureLoader::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
        SDL_RenderCopy(WindowManager::renderer, tex, &src, &dest);
    }
    
}