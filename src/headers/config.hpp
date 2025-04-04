#pragma once

// Include all the headers you need for the entire program

#include <SDL2/SDL.h>
#include <set>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <queue>
#include <cmath>
#include <future>
#include <chrono>

namespace GameEngine
{
    enum class GhostState {
        CHASE = 0, 
        SEEK = 1,
        AFRAID = 2
    };

    const int INIT_BLINKY_X = 13;
    const int INIT_BLINKY_Y = 13;
    const int INIT_PINKY_X = 12;
    const int INIT_PINKY_Y = 14;
    const int INIT_INKY_X = 11;
    const int INIT_INKY_Y = 13;
    const int INIT_PACMAN_X = 12;
    const int INIT_PACMAN_Y = 23;
} // namespace GameEngine

// Your own headers
#include "Math.hpp"
#include "Acceuil.hpp"
#include "GameOver.hpp"
#include "FontsLoader.hpp"
#include "Map.hpp"
#include "WindowManager.hpp"
#include "CollisionSystem.hpp"
#include "Pacman.hpp"
#include "TextureLoader.hpp"


#include "Blinky.hpp"
#include "Pinky.hpp"
#include "Inky.hpp"

#include "Tree.hpp"




