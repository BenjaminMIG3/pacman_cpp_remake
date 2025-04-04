#include "headers/WindowManager.hpp"

namespace GameEngine {

    SDL_Renderer* WindowManager::renderer = nullptr;
    Map* WindowManager::map = nullptr;
    CollisionSystem* WindowManager::collisionSystem = nullptr;
    
    //Constructeur de la classe
    WindowManager::WindowManager(){
        if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
            throw std::runtime_error("Failed to initialize SDL2 with error: " + std::string(SDL_GetError()));
        }
        else {
            std::cout << "SDL2 Sucessfully initialized " << std::endl;

            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

            if(window == nullptr) {
                throw std::runtime_error("Failed to create a window");
            }

            renderer = SDL_CreateRenderer(window, -1, 0);

            SDL_SetRenderDrawColor(renderer, 0,0, 0, 255);

            SDL_RenderPresent(renderer);

            this->acceuil = new Acceuil();
            this->gameOver = new GameOver();

            pacman = new Pacman(INIT_PACMAN_X,INIT_PACMAN_Y);

            map = new Map();

            map->setPlayer(pacman);

            collisionSystem = new CollisionSystem();

            blinky = new Blinky(INIT_BLINKY_X, INIT_BLINKY_Y, pacman);

            pinky = new Pinky(INIT_PINKY_X, INIT_PINKY_Y, pacman);

            inky = new Inky(INIT_INKY_X,INIT_INKY_Y,pacman,blinky);

            fontsWindowManager = new FontsLoader("assets/fonts/atari.ttf", 100, fontRect);

            fontsWindowManager->setMessage("PRESS C TO PLAY");

            etat = ACCEUIL;
        }
    }

    //Destructeur de la classe
    WindowManager::~WindowManager(){
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        map->~Map();
        pacman->~Pacman();
        blinky->~Blinky();
        pinky->~Pinky();
        inky->~Inky();
        fontsWindowManager->~FontsLoader();
        TTF_Quit();
        SDL_Quit();
        std::cout << "SDL2 Quitted " << std::endl;
    }

    //Gerer les inputs
    void WindowManager::handleEvents(){
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
        }
        if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {   
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_UP:
                    pacman->direction = UP;
                    break;
                case SDLK_DOWN:
                    pacman->direction = DOWN;
                    break;
                case SDLK_RIGHT:
                    pacman->direction = RIGHT;
                    break;
                case SDLK_LEFT:
                    pacman->direction = LEFT;
                    break;
                case SDLK_d:
                    pacman->vie -= 1;
                    break;
                case SDLK_h:
                    if(etat == JEU) {
                        blinky->ghostState = GhostState::SEEK;
                        pinky->ghostState = GhostState::SEEK;
                        inky->ghostState = GhostState::SEEK;
                    }
                    break;
                case SDLK_b:
                    if(etat == JEU) {
                        blinky->ghostState = GhostState::AFRAID;
                        pinky->ghostState = GhostState::AFRAID;
                        inky->ghostState = GhostState::AFRAID;
                    }
                    break;
                case SDLK_c:
                    if(etat == JEU) {
                        blinky->ghostState = GhostState::CHASE;
                        pinky->ghostState = GhostState::CHASE;
                        inky->ghostState = GhostState::CHASE;
                        map->mapEtat = MapEtat::CHASING;
                    }
                    break;
                case SDLK_i:
                    if(etat == JEU) {
                        map->mapEtat = MapEtat::IDLE;
                    }
                    break;
                case SDLK_SPACE:
                    if(etat == ACCEUIL) {
                        pacman->restartGame(INIT_PACMAN_X,INIT_PACMAN_Y);
                        blinky->restartGame(INIT_BLINKY_X, INIT_BLINKY_Y);
                        pinky->restartGame(INIT_PINKY_X, INIT_PINKY_Y);
                        inky->restartGame(INIT_INKY_X,INIT_INKY_Y);
                        this->etat = JEU;
                        map->mapEtat = IDLE;
                    }else if(etat == GAME_OVER) {
                        //Passer de GAME_OVER à JOUER + RESET SCORE + RESET POS du JOUEUR + POS Ghost + VIE du JOUEUR
                        pacman->restartGame(INIT_PACMAN_X,INIT_PACMAN_Y);
                        blinky->restartGame(INIT_BLINKY_X, INIT_BLINKY_Y);
                        pinky->restartGame(INIT_PINKY_X, INIT_PINKY_Y);
                        inky->restartGame(INIT_INKY_X,INIT_INKY_Y);
                        this->etat = JEU;
                        map->mapEtat = IDLE;
                    }
                default:
                    break;
            }
        }
    }

    //Gerer les gameObject (mouvements ...)
    void WindowManager::update(){
        map->update();
        if(map->mapEtat == MapEtat::CHASING) {
            pacman->update();  
            blinky->update();
            pinky->update();
            inky->update();
            // if(WindowManager::collisionSystem->checkCollisionWithPacman(blinky->pos, pacman->playerPos)){
            //     pacman->vie--;
            //     blinky->restartPos(INIT_BLINKY_X, INIT_BLINKY_Y);
            //     pacman->resetPos(INIT_PACMAN_X,INIT_PACMAN_Y);
            //     pinky->restartPos(INIT_PINKY_X, INIT_PINKY_Y);
            //     inky->restartPos(INIT_INKY_X,INIT_INKY_Y);
            //     WindowManager::map->mapEtat = MapEtat::IDLE;
            // }
            if(WindowManager::collisionSystem->checkCandy(pacman->playerPos[0], pacman->playerPos[1])){
                pacman->score += 20; 
                this->map->getMap()[pacman->playerPos[1]][pacman->playerPos[0]] = 0;
            }
            if(WindowManager::collisionSystem->checkCherry(pacman->playerPos[0], pacman->playerPos[1])){
                pacman->score += 50; 
                blinky->ghostState = GhostState::AFRAID;
                pinky->ghostState = GhostState::AFRAID;
                inky->ghostState = GhostState::AFRAID;
                blinky->setStateAfterDelay(GhostState::CHASE, 5000);
                inky->setStateAfterDelay(GhostState::CHASE, 5000);
                pinky->setStateAfterDelay(GhostState::CHASE, 5000);
                this->map->getMap()[pacman->playerPos[1]][pacman->playerPos[0]] = 0;
            }
            //Gere les etats du jeu 
            if(this->etat == JEU) {
                if(pacman->vie <= 0) {
                    etat = state::GAME_OVER;
                } 
            } 
        }
    }

    //Gere le rendu 
    void WindowManager::render(){
        SDL_RenderClear(renderer);
        switch (etat)
        {
        case ACCEUIL:
            this->acceuil->draw();
            break;
        case JEU:
            map->drawMap();
            pacman->render();
            blinky->render();
            pinky->render();
            inky->render();
            break;
        case GAME_OVER:
            this->gameOver->draw();
            break;
        default:
            break;
        }

        switch (map->mapEtat)
        {
        case MapEtat::IDLE:
            if(etat == JEU) {
                fontsWindowManager->drawFont();
            }
            break;
        
        default:
            break;
        }
        SDL_RenderPresent(renderer);
    }

    //Boucle principale du jeu
    void WindowManager::show(){
        while (!quit) {
            frameStart = SDL_GetTicks();

            handleEvents();
            update();
            render();

            frameTime = SDL_GetTicks() - frameStart;

            if(frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
}