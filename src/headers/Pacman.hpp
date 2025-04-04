#pragma once 
#include "config.hpp"


namespace GameEngine {

    class CollisionSystem;

    class Pacman {

        enum {
            NONE = -1,
            LEFT = 0,
            RIGHT = 1,
            UP = 2,
            DOWN = 3
        };

        public:

            Pacman(int x, int y);

            ~Pacman();

            void render();

            void update();

            int direction;

            void move();

            int playerPos[2];

            int getScore();

            int vie;

            void restartGame(int x, int y);

            void resetPos(int x, int y);

            int score;

        private:

            int xpos;
            int ypos;

            SDL_Rect srcR, destR, heartSrc, heartDest;

            
            SDL_Texture* currentTexture;

            SDL_Texture* heartTextures;

            void fillLeftTextures();
            void fillRightTextures();
            void fillUpTextures();
            void fillDownTextures();

            std::vector<SDL_Texture*> leftTextures;
            std::vector<SDL_Texture*> rightTextures;
            std::vector<SDL_Texture*> upTextures;
            std::vector<SDL_Texture*> downTextures;

            std::vector<SDL_Texture*>* currentTextures;

            const int animationSpeed = 20;
            int currentFrameIndex;

            uint32_t lastMoveTime;  // Time of the last move
            uint32_t moveDelay;

            
            


    };

    
}