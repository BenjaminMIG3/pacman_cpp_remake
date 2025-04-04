#include "headers/CollisionSystem.hpp"

namespace GameEngine {


    /**
     * Constructeur de la class CollisionSystem
     * @param uneMap pointeur d'un objet map
     */
    CollisionSystem::CollisionSystem() {
    }

    /**
     * Retourne true si mouvement possible 
     * @param x position x du joueur
     * @param y position y du joueur
     * @param direction U = UP ; D = DOWN ; L = LEFT ; R = RIGHT
     * @return true si mouvement possible false sinon
     */
    bool CollisionSystem::checkMovements(int x, int y, int direction) {
        //std::cout << "Case actuelle ["<<x<<"]["<<y<<"]"<< std::endl;
        switch (direction) {
            case 2:
                y -= 1;
                break;
            case 3:
                y += 1;
                break;
            case 0:
                x -= 1;
                break;
            case 1:
                x += 1;
                break;
            default:
                throw std::invalid_argument("Veuillez entrer une direction correcte");
        }
        return WindowManager::map->getMap()[y][x] == 0 || WindowManager::map->getMap()[y][x] == 7 || (WindowManager::map->getMap()[y][x] == 9 && WindowManager::map->mapEtat == 1)  || (WindowManager::map->getMap()[y][x] == 8) || (WindowManager::map->getMap()[y][x] == 10);
    }

    /**
     * Fonction qui retourne true si un bonbon se trouve aux coordonnées passées en paramètre
     * @param x pos X
     * @param y pos Y
     */
    bool CollisionSystem::checkCandy(int x, int y) {
        return WindowManager::map->getMap()[y][x] == 7;
    }

    /**
     * Fonction qui retourne true si une cerise se trouve aux coordonnées passées en paramètre
     * @param x pos X
     * @param y pos Y
     */
    bool CollisionSystem::checkCherry(int x, int y) {
        return WindowManager::map->getMap()[y][x] == 10;
    }

    /**
     * Retourne true si les positions sont égales
     * @param pos1 (int) position 1
     * @param pos2 (int) position 2
     * @return bool 
     */
    bool CollisionSystem::checkCollisionWithPacman(int* pos1, int* pos2) {
        return (pos1[0] == pos2[0] && pos1[1] == pos2[1]);
    }

}
