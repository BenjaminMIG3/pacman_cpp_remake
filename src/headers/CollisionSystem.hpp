#pragma once

#include "config.hpp"

namespace GameEngine {

    class Map;
    class WindowManager;

    class CollisionSystem {

        public :

            CollisionSystem();

            bool checkMovements(int x, int y, int direction);
            bool checkCandy(int x, int y);
            bool checkCherry(int x, int y);
            bool checkCollisionWithPacman(int* pos1, int* pos2);

        private :
            
    };
}