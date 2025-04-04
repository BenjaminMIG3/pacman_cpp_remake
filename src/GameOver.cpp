#include "headers/GameOver.hpp"

namespace GameEngine {

    GameOver::GameOver() {
        this->fontsLoader = new GameEngine::FontsLoader("PRESS SPACE TO RESTART", 40, this->fontRect);
        
        this->ripTexture = GameEngine::TextureLoader::getPlayerTexture("assets/gameOver/rip.png");

        this->srcR.x = 0;
        this->srcR.y = 0;
        this->srcR.w = this->destR.w = 200;
        this->srcR.h = this->destR.h = 224;
        this->destR.x = 150;
        this->destR.y = 80;
    }

    void GameOver::draw(){
        this->fontsLoader->drawFont();
        GameEngine::TextureLoader::draw(this->ripTexture, srcR, destR);
    }
}