#pragma once 
#include "config.hpp"

namespace GameEngine{
    
    class Math {

        public :
        
            static int roundByDecimal(int num1, int num2, float margeHaute, float margeBasse);

            static bool pileOrFace();

            static int* getRandomPos();

            static int getRandomDirection();
            
            static int* getHidePositionBlinky();

            static int* getHidePositionPinky();

            static int* getHidePositionInky();

    };
}