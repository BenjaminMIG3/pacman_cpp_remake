#include "headers/WindowManager.hpp"

GameEngine::WindowManager *window = nullptr;

int main(){

    window = new GameEngine::WindowManager();

    // Boucle SDL pour maintenir la fenêtre ouverte et gérer les événements
    window->show();

    window->~WindowManager();
    
    return 0;
}