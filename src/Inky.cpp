#include "headers/Inky.hpp"

namespace GameEngine {
        Inky::Inky(int x, int y, Pacman* pacmanPlayer, Blinky* blinkyPlayer) {
        this->pacman = pacmanPlayer;
        this->blinky = blinkyPlayer;
        this->pos[0] = x;
        this->pos[1] = y;

        texture = TextureLoader::getPlayerTexture("assets/ghosts/inky.png");
        deadTexture = TextureLoader::getPlayerTexture("assets/ghosts/dead.png");

        xpos = x * 20;
        ypos = y * 20;
        destR.x = xpos;
        destR.y = ypos;
        srcR.h = 20;
        srcR.w = 20;
        srcR.x = 0;
        srcR.y = 0;
        destR.h = 20;
        destR.w = 20;
        dead = false;
        this->lastMoveTime = 0;       // Initialize lastMoveTime
        this->moveDelay = 100;
        this->hideDelay = 200;
        this->lastRefreshPathTime = 0;
        this->refreshDirectionPathTime = 100;
        this->direction = NONE;

        this->ghostState = GhostState::CHASE;
        this->hidePos = Math::getHidePositionInky();
    }

    Inky::~Inky() {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(deadTexture);
    }

    void Inky::restartGame(int x, int y) {
        std::cout << "Restart inky stats \n";
        restartPos(x,y);
        dead = false;
    }

    void Inky::render() {
        if (ghostState == GhostState::AFRAID) {
            SDL_RenderCopy(WindowManager::renderer, deadTexture, &srcR, &destR);
        } else {
            SDL_RenderCopy(WindowManager::renderer, texture, &srcR, &destR);
        }
    }

    /**
     * Fonction redéfinie permettant la logique de Blinky
     */
    void Inky::move() {
        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastMoveTime < moveDelay) {
            return;  // Not enough time has passed, exit the function
        }

        switch (direction) {
            case UP:
                    pos[1] -= 1;
                    this->ypos = this->pos[1] * 20;
                break;
            case DOWN:
                    pos[1] += 1;
                    this->ypos = this->pos[1] * 20;
                break;
            case LEFT:
                    pos[0] -= 1;
                    this->xpos = this->pos[0] * 20;
                break;
            case RIGHT:
                    pos[0] += 1;
                    this->xpos = this->pos[0] * 20;
                break;
            case NONE:
                std::cout << "Blinky n'a pas de direction" << std::endl;
                break;
        }

        lastMoveTime = currentTime;
        destR.x = xpos;
        destR.y = ypos;
    }

    void Inky::update() {
        uint32_t currentTime = SDL_GetTicks();


        if(ghostState == GhostState::AFRAID || ghostState == GhostState::SEEK) {
            if(WindowManager::map->mapEtat == 1) {
                if((currentTime - lastRefreshPathTime >= refreshDirectionPathTime)) {
                    this->recalculatePath();
                }
                if (currentTime - lastMoveTime >= hideDelay + 50) {
                    
                    if (!directionPath.empty()) {
                        this->direction = directionPath[0];
                        directionPath.erase(directionPath.begin());

                        if (this->direction != NONE) {
                            this->move();
                        }
                    }
                }
            }    
        } 
        else 
        {
            if(WindowManager::map->mapEtat == 1) {
                if((currentTime - lastRefreshPathTime >= refreshDirectionPathTime)) {
                    this->recalculatePath();
                }
                if (currentTime - lastMoveTime >= moveDelay + 50) {
                    if (!directionPath.empty()) {
                        this->direction = directionPath[0];
                        directionPath.erase(directionPath.begin());

                        if (this->direction != NONE) {
                            this->move();
                        }
                    }
                }
            }    
        }
    }

    /**
     * Recalculer le chemin le plus optimal
     */
    void Inky::recalculatePath() {

        Position inkyPosition(this->pos[0], this->pos[1]);

        this->directionPath.clear();
        
        switch (this->ghostState)
        {
            case GhostState::CHASE: {
                Position pacmanPosition(this->pacman->playerPos[0], this->pacman->playerPos[1]);
                Position blinkyPosition(this->blinky->pos[0], this->blinky->pos[1]);
                for(Node* node : Tree::getPathInkyToPacman(inkyPosition, pacmanPosition, blinkyPosition, pacman->direction)) {
                    this->directionPath.push_back(node->direction);
                }
                break;
            }
            case GhostState::SEEK: {
                Position hidePosition(hidePos[0], hidePos[1]);
                //Se mets dans une case aléatoire selon le coté défini
                for(Node* node : Tree::getPathToBase(inkyPosition, hidePosition)) {
                    this->directionPath.push_back(node->direction);
                }
                break;
            }
            case GhostState::AFRAID: {
                //Retourne dans la base
                Position basePosition(INIT_INKY_X, INIT_INKY_Y);
                for(Node* node : Tree::getPathToBase(inkyPosition, basePosition)) {
                    this->directionPath.push_back(node->direction);
                }
                break;
            } 
        }


        this->lastRefreshPathTime = SDL_GetTicks();
    }

    void Inky::restartPos(int x, int y) {
        this->ghostState = GhostState::CHASE;
        this->xpos = x * 20;
        this->ypos = y * 20;
        this->pos[0] = x;
        this->pos[1] = y;
        destR.x = xpos;
        destR.y = ypos;
    }
}