#include "headers/Pacman.hpp"

namespace GameEngine {


    Pacman::Pacman(int x, int y){
        score = 0;
        xpos = x * 20;
        ypos = y * 20;
        srcR.h = destR.h = heartDest.h = heartSrc.h = 20;
        srcR.x = heartSrc.x = 0;
        srcR.y = heartSrc.y = 0;
        destR.w = srcR.w = heartDest.w = heartSrc.w = 20;

        heartDest.x = 380;
        heartDest.y = 550;
        
        fillLeftTextures();
        fillRightTextures();
        fillDownTextures();
        fillUpTextures();
        heartTextures = TextureLoader::getPlayerTexture("assets/pacman/heart.png");
        currentFrameIndex = 0;
        direction = NONE;
        currentTextures = &rightTextures;
        currentTexture = (*currentTextures)[currentFrameIndex];

        this->playerPos[0] = x;
        this->playerPos[1] = y;
        this->lastMoveTime = 0;       // Initialize lastMoveTime
        this->moveDelay = 100;
        this->vie = 3; 
    }

    Pacman::~Pacman(){

        for (unsigned int i = 0; i < leftTextures.size(); i++)
        {
            SDL_DestroyTexture(leftTextures[i]);
        }

        for (unsigned int i = 0; i < rightTextures.size(); i++)
        {
            SDL_DestroyTexture(rightTextures[i]);
        }

        for (unsigned int i = 0; i < upTextures.size(); i++)
        {
            SDL_DestroyTexture(upTextures[i]);
        }

        for (unsigned int i = 0; i < downTextures.size(); i++)
        {
            SDL_DestroyTexture(downTextures[i]);
        }
    }

    void Pacman::fillLeftTextures(){
        for(unsigned int i = 0; i < 3; i++) {
            std::string path = "assets/pacman/pacmanLeft/left" + std::to_string(i) + ".png";
            leftTextures.push_back(TextureLoader::getPlayerTexture(path.c_str()));
        }
    }

    void Pacman::fillRightTextures(){
        for(unsigned int i = 0; i < 3; i++) {
            std::string path = "assets/pacman/pacmanRight/right" + std::to_string(i) + ".png";
            rightTextures.push_back(TextureLoader::getPlayerTexture(path.c_str()));
        }
    }

    void Pacman::fillDownTextures(){
        for(unsigned int i = 0; i < 3; i++) {
            std::string path = "assets/pacman/pacmanDown/down" + std::to_string(i) + ".png";
            downTextures.push_back(TextureLoader::getPlayerTexture(path.c_str()));
        }
    }

    void Pacman::fillUpTextures(){
        for(unsigned int i = 0; i < 3; i++) {
            std::string path = "assets/pacman/pacmanUp/up" + std::to_string(i) + ".png";
            upTextures.push_back(TextureLoader::getPlayerTexture(path.c_str()));
        }
    }

    void Pacman::render(){
        SDL_RenderCopy(WindowManager::renderer, currentTexture, &srcR, &destR);
        heartDest.x = 380;
        for(int i = 0; i < this->vie; i++){
            SDL_RenderCopy(WindowManager::renderer, heartTextures, NULL, &heartDest);
            heartDest.x += 25;
        }
    }

    void Pacman::update(){
        destR.x = xpos;
        destR.y = ypos;

        switch (direction)
        {
        case LEFT:
            currentTextures = &leftTextures;
            break;
        case RIGHT:
            currentTextures = &rightTextures;
            break;
        case UP:
            currentTextures = &upTextures;
            break;
        case DOWN:
            currentTextures = &downTextures;
            break;
        default:
            break;
        }

        if (SDL_GetTicks() % animationSpeed == 0) {
            currentFrameIndex = (currentFrameIndex + 1) % currentTextures->size();
            currentTexture = (*currentTextures)[currentFrameIndex];
        }

        if(this->direction != NONE) {
            this->move();
        }
    }

    int Pacman::getScore(){
        return this->score;
    }

    void Pacman::move(){

        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastMoveTime < moveDelay) {
            return;  // Not enough time has passed, exit the function
        }
        
        switch(direction){
            case UP:
                if(WindowManager::collisionSystem->checkMovements(this->playerPos[0], this->playerPos[1], UP)){
                    playerPos[1] -= 1;
                    this->ypos = this->playerPos[1] * 20;
                }
                break;
            case DOWN:
                if(WindowManager::collisionSystem->checkMovements(this->playerPos[0], this->playerPos[1], DOWN)){
                    playerPos[1] += 1;
                    this->ypos = this->playerPos[1] * 20;
                }
                break;
            case LEFT:
                if(WindowManager::collisionSystem->checkMovements(this->playerPos[0], this->playerPos[1], LEFT)){
                    playerPos[0] -= 1;
                    this->xpos = this->playerPos[0] * 20;
                }
                break;
            case RIGHT:
                if(WindowManager::collisionSystem->checkMovements(this->playerPos[0], this->playerPos[1], RIGHT)){
                    playerPos[0] += 1;
                    this->xpos = this->playerPos[0] * 20;
                }
                break;
            case NONE:
                break;
        }
        if(this->playerPos[0] == 0 && this->playerPos[1] == 14 && this->direction == LEFT) {
            this->playerPos[0] = 23;
            this->playerPos[1] = 14;
            this->xpos = 23*20;
            this->ypos = 14 * 20;
        }
        if(this->playerPos[0] == 23 && this->playerPos[1] == 14 && this->direction == RIGHT) {
            this->playerPos[0] = 0;
            this->playerPos[1] = 14;
            this->xpos = 0;
            this->ypos = 14 * 20;
        }

        lastMoveTime = currentTime;
    }


    void Pacman::restartGame(int x , int y){
        this->vie = 3;
        this->score = 0;
       this->resetPos(x,y);
    }

    void Pacman::resetPos(int x, int y) {
        this->xpos = 20 * x;
        this->ypos = 20 * y;
        this->direction = NONE;
        this->playerPos[0] = x;
        this->playerPos[1] = y;
        destR.x = xpos;
        destR.y = ypos;
    }

}