#pragma once

#include "config.hpp"

namespace GameEngine {

    class Tile;
    class FontsLoader;
    class Pacman;
    class CollisionSystem;

    class Map {

        enum : int{
            
            BLACK_TILE = 0,
            V_TILE = 1,
            CURVED_DOWN_LEFT = 2,
            CURVED_DOWN_RIGHT = 3,
            CURVED_UP_LEFT = 4,
            CURVED_UP_RIGHT = 5,
            H_TILE = 6,
            CANDY_TILE = 7,
            VOID_TILE = 8,
            CHANGING_TILE = 9,
            CHERRY_TILE = 10
        };

        enum gameState {
            IDLE = 0,
            CHASING = 1
        };

        public: 

            Map();
            ~Map();

            void loadMap(int arr[26][24]);
            void drawMap();
            int (*getMap())[24];

            void setPlayer(Pacman* joueur);

            void setMessageToFonts();

            void update();

            int mapEtat;

        private: 

            void setCandyIntoTheMap();

            void setCherryIntoTheMap();

            int checkNbCherryInMap();

            int checkNbCandyInMap();

            const uint32_t maxCandy = 20;

            const uint32_t maxCherry = 5; 

            SDL_Rect src, dest;

            SDL_Rect fontRect = {80, 500, 100, 20};

            SDL_Texture* hTile; 
            SDL_Texture* vTile; 
            SDL_Texture* curveUpLeft; 
            SDL_Texture* curveUpRight; 
            SDL_Texture* curveDownLeft;
            SDL_Texture* curveDownRight;
            SDL_Texture* blackTile;
            SDL_Texture* cherryTile;
            SDL_Texture* candy;

            FontsLoader* fontsLoader;

            std::vector<SDL_Texture*> allText;

            std::vector<Pacman*> candies;

            

            Pacman* player;

            int map[26][24];

    };

}