#pragma once 

#include "config.hpp"

namespace GameEngine {

    class Pinky {

        public : 
            Pinky(int x, int y, Pacman* pacmanPlayer);
            ~Pinky();

            void update();
            void move();
            void render();

            int pos[2];

            int direction;

            void restartGame(int x, int y);
            void recalculatePath();

            void restartPos(int x, int y);

            bool dead;

            GhostState ghostState = GhostState::CHASE;

            void setStateAfterDelay(GhostState newState, int delayMilliseconds) {
                // Démarrer un thread pour gérer le délai et le changement d'état
                std::thread([=]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
                    
                    // Boucle de vérification jusqu'à ce que la condition soit remplie
                    while (!(this->pos[0] == INIT_PINKY_X && this->pos[1]  == INIT_PINKY_Y)) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Attendre 100 ms entre chaque vérification
                    }
                    
                    ghostState = newState;
                    std::cout << "Ghost state changed to AFRAID after reaching base." << std::endl;
                }).detach(); // Détacher le thread pour qu'il s'exécute en arrière-plan
            }

        private :

            Pacman* pacman;

            int xpos, ypos;

            SDL_Texture* texture;

            SDL_Texture* deadTexture;

            SDL_Rect srcR, destR;

            uint32_t lastMoveTime, lastRefreshPathTime;  // Time of the last move
            uint32_t moveDelay, hideDelay;
            uint32_t refreshDirectionPathTime;

            std::vector<int> directionPath;

            int* hidePos;

    };
}