#pragma once
#include "config.hpp"

namespace GameEngine {
    class Inky {
        public :

            Inky(int x, int y, Pacman* pacmanPlayer, Blinky* blinkyPlayer);
            ~Inky();

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
                    // Variables de condition
                    bool conditionMet = false;
                    auto startTime = std::chrono::steady_clock::now();
                    auto endTime = startTime + std::chrono::milliseconds(delayMilliseconds);
                    
                    // Boucle de vérification jusqu'à ce que la condition soit remplie ou que le délai soit écoulé
                    while (!conditionMet && std::chrono::steady_clock::now() < endTime) {
                        if (this->pos[0] == INIT_INKY_X && this->pos[1] == INIT_INKY_Y) {
                            conditionMet = true;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Attendre 100 ms entre chaque vérification
                    }
                    
                    // Si la condition est remplie, changer l'état du fantôme
                    if (conditionMet) {
                        ghostState = newState;
                        std::cout << "Ghost state changed to AFRAID after reaching base." << std::endl;
                    } else {
                        std::cout << "Timeout reached before reaching base." << std::endl;
                    }
                }).detach(); // Détacher le thread pour qu'il s'exécute en arrière-plan
            }

        private : 

            Pacman* pacman;

            Blinky* blinky;

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