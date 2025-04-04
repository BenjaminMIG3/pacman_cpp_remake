#include "headers/Acceuil.hpp"

namespace GameEngine {
    Acceuil::Acceuil() {
        this->fontsLoader = new GameEngine::FontsLoader("PRESS SPACE TO PLAY", 40, this->fontRect);
        
        this->logoPacman = GameEngine::TextureLoader::getPlayerTexture("assets/acceuil/pacmanLogo.png");

        this->srcR.x = 0;
        this->srcR.y = 0;
        this->srcR.w = this->destR.w = 300;
        this->srcR.h = this->destR.h = 150;
        this->destR.x = 100;
        this->destR.y = 170;
    }

    void Acceuil::draw(){
        this->fontsLoader->drawFont();
        GameEngine::TextureLoader::draw(logoPacman, srcR, destR);
    }
}