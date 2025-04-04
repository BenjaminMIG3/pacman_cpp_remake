#include "headers/Tree.hpp"

namespace GameEngine {

    // Fonction pour calculer la distance de Manhattan entre deux positions
    int Tree::manhattanDistance(const Position& a, const Position& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    std::vector<Node*> Tree::getPathInkyToPacman(const Position& inkyPos, const Position& pacmanPos, const Position& blinkyPos, int direction) {
        //Chercher la position futur de blinky selon sa direction
        int goalPos[2] = {pacmanPos.x,pacmanPos.y};

        //Recuperer le double de la distance 
        int distBlinkyPacman = Tree::manhattanDistance(blinkyPos, pacmanPos) * 2;

        //Direction de pacman
       //int pacmanDir = direction;

        if (direction == LEFT) {
            goalPos[0] -= distBlinkyPacman; // Adjust goalPos if Pac-Man is moving left
            if (goalPos[0] < 0) {
                goalPos[0] = 0;
            }
        } else if (direction == RIGHT) {
            goalPos[0] += distBlinkyPacman; // Adjust goalPos if Pac-Man is moving right
            if (goalPos[0] > 23) { // Assurez-vous que goalPos[0] ne dépasse pas la largeur maximale (23)
                goalPos[0] = 23;
            }
        } else if (direction == UP) {
            goalPos[1] -= distBlinkyPacman; // Adjust goalPos if Pac-Man is moving up
            if (goalPos[1] < 0) {
                goalPos[1] = 0;
            }
        } else if (direction == DOWN) {
            goalPos[1] += distBlinkyPacman; // Adjust goalPos if Pac-Man is moving down
            if (goalPos[1] > 25) { // Assurez-vous que goalPos[1] ne dépasse pas la hauteur maximale (25)
                goalPos[1] = 25;
            }
        }
        
        // Vérifier que goalPos reste dans les limites du tableau 26x24
        if (goalPos[0] < 0) {
            goalPos[0] = 0;
        } else if (goalPos[0] > 23) {
            goalPos[0] = 23;
        }
        if (goalPos[1] < 0) {
            goalPos[1] = 0;
        } else if (goalPos[1] > 25) {
            goalPos[1] = 25;
        }

        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;

        bool visitedLocation[26][24] = {};

        const Position futurPos(goalPos[0], goalPos[1]);

        //Création du noeud racine
        priorityQueue.push(new Node(inkyPos, NONE, 0, Tree::manhattanDistance(inkyPos, futurPos)));
        visitedLocation[inkyPos.x][inkyPos.y] = true;

        Node* goalNode = nullptr;

        //TODO : Chercher les voisins une fois avoir determiné la position future de pacman

        while (!priorityQueue.empty()) {
            Node* currentNode = priorityQueue.top();
            priorityQueue.pop();

            if (currentNode->pos.x == goalPos[0] && currentNode->pos.y == goalPos[1]) {
                goalNode = currentNode;
                break;
            }

            std::vector<Node*> neighbors = Tree::generateNeighborsForBlinkyPath(currentNode, futurPos);
            for (Node* neighbor : neighbors) {
                if (!visitedLocation[neighbor->pos.x][neighbor->pos.y]) {
                    priorityQueue.push(neighbor);
                    visitedLocation[neighbor->pos.x][neighbor->pos.y] = true;
                }
            }
        }
        std::vector<Node*> path;

        if (goalNode != nullptr) {
            path = Tree::getPath(goalNode);
            //std::cout << "Voici la cible de inky : [" << goalNode->pos.x << "][" << goalNode->pos.y << "] \n";
        } else {
            //std::cout << "Aucun chemin trouvé vers Pac-Man." << std::endl;
        }

        // Libération de la mémoire
        while (!priorityQueue.empty()) {
            delete priorityQueue.top();
            priorityQueue.pop();
        }

        memset(visitedLocation, 0, sizeof(visitedLocation));
        memset(goalPos, 0, sizeof(goalPos));

        return path;
    }

    std::vector<Node*> Tree::getPathPinkyToPacman(const Position& pinkyPos, const Position& pacmanPos, int direction) {

        //Chercher la position futur de pacman selon sa direction
        int goalPos[2] = {pacmanPos.x,pacmanPos.y};

        int compteur = 0;

        switch (direction) {
            case UP:
                while (compteur < 4 && WindowManager::collisionSystem->checkMovements(pacmanPos.x, pacmanPos.y - compteur, UP)) {
                    compteur++;
                }
                goalPos[1] -= compteur;
                break;
            case DOWN:
                while (compteur < 4 && WindowManager::collisionSystem->checkMovements(pacmanPos.x, pacmanPos.y + compteur, DOWN)) {
                    compteur++;
                }
                goalPos[1] += compteur;
                break;
            case LEFT:
                while (compteur < 4 && WindowManager::collisionSystem->checkMovements(pacmanPos.x - compteur, pacmanPos.y, LEFT)) {
                    compteur++;
                }
                goalPos[0] -= compteur;
                break;
            case RIGHT:
                while (compteur < 4 && WindowManager::collisionSystem->checkMovements(pacmanPos.x + compteur, pacmanPos.y, RIGHT)) {
                    compteur++;
                }
                goalPos[0] += compteur;
                break;
            default:
                break;
        }

        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
        bool visitedLocation[26][24] = {};

        const Position futurPos(goalPos[0], goalPos[1]);

        //Création du noeud racine
        priorityQueue.push(new Node(pinkyPos, NONE, 0, Tree::manhattanDistance(pinkyPos, futurPos)));
        visitedLocation[pinkyPos.x][pinkyPos.y] = true;

        Node* goalNode = nullptr;

        //TODO : Chercher les voisins une fois avoir determiné la position future de pacman

        while (!priorityQueue.empty()) {
            Node* currentNode = priorityQueue.top();
            priorityQueue.pop();

            if (currentNode->pos.x == goalPos[0] && currentNode->pos.y == goalPos[1]) {
                goalNode = currentNode;
                break;
            }

            std::vector<Node*> neighbors = Tree::generateNeighborsForBlinkyPath(currentNode, futurPos);
            for (Node* neighbor : neighbors) {
                if (!visitedLocation[neighbor->pos.x][neighbor->pos.y]) {
                    priorityQueue.push(neighbor);
                    visitedLocation[neighbor->pos.x][neighbor->pos.y] = true;
                }
            }
        }
        std::vector<Node*> path;

        if (goalNode != nullptr) {
            path = Tree::getPath(goalNode);
            //std::cout << "Voici la position anticipée de pacman dans max " << compteur << " deplacements : [" << goalNode->pos.x << "][" << goalNode->pos.y << "] \n";
        } else {
            //std::cout << "Aucun chemin trouvé vers Pac-Man." << std::endl;
        }

        // Libération de la mémoire
        while (!priorityQueue.empty()) {
            delete priorityQueue.top();
            priorityQueue.pop();
        }

        memset(visitedLocation, 0, sizeof(visitedLocation));
        memset(goalPos, 0, sizeof(goalPos));

        return path;
    }

    // Fonction pour obtenir le chemin vers Pac-Man à partir de la position de Blinky
    std::vector<Node*> Tree::getPathBlinkyToPacman(const Position& blinkyPosition, const Position& pacmanPosition) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
        static bool visitedLocation[26][24] = {}; // Initialisation statique, si nécessaire
        
        priorityQueue.push(new Node(blinkyPosition, NONE, 0, Tree::manhattanDistance(blinkyPosition, pacmanPosition)));
        visitedLocation[blinkyPosition.x][blinkyPosition.y] = true;

        Node* goalNode = nullptr;

        // Boucle principale de l'algorithme A*
        while (!priorityQueue.empty()) {
            Node* currentNode = priorityQueue.top();
            priorityQueue.pop();

            if (currentNode->pos.x == pacmanPosition.x && currentNode->pos.y == pacmanPosition.y) {
                goalNode = currentNode;
                break;
            }

            std::vector<Node*> neighbors = Tree::generateNeighborsForBlinkyPath(currentNode, pacmanPosition);
            for (Node* neighbor : neighbors) {
                if (!visitedLocation[neighbor->pos.x][neighbor->pos.y]) {
                    priorityQueue.push(neighbor);
                    visitedLocation[neighbor->pos.x][neighbor->pos.y] = true;
                }
            }
        }

        std::vector<Node*> path;

        if (goalNode != nullptr) {
            path = Tree::getPath(goalNode);
        } else {
            std::cout << "Aucun chemin trouvé vers Pac-Man." << std::endl;
        }

        // Libération de la mémoire
        while (!priorityQueue.empty()) {
            delete priorityQueue.top();
            priorityQueue.pop();
        }

        memset(visitedLocation, 0, sizeof(visitedLocation));

        return path;
    }


    // Fonction pour générer les voisins d'un nœud donné
    std::vector<Node*> Tree::generateNeighborsForBlinkyPath(Node* node, const Position& pacmanPos) {
        std::vector<Node*> neighbors;

        if (WindowManager::collisionSystem->checkMovements(node->pos.x, node->pos.y, LEFT)) {
            neighbors.push_back(new Node(Position(node->pos.x - 1, node->pos.y), LEFT, node->g + 1, manhattanDistance(Position(node->pos.x + 1, node->pos.y), pacmanPos), node));
        }
        if (WindowManager::collisionSystem->checkMovements(node->pos.x, node->pos.y, RIGHT)) {
            neighbors.push_back(new Node(Position(node->pos.x + 1, node->pos.y), RIGHT, node->g + 1, manhattanDistance(Position(node->pos.x - 1, node->pos.y), pacmanPos), node));
        }
        if (WindowManager::collisionSystem->checkMovements(node->pos.x, node->pos.y, UP)) {
            neighbors.push_back(new Node(Position(node->pos.x, node->pos.y - 1), UP, node->g + 1, manhattanDistance(Position(node->pos.x, node->pos.y - 1), pacmanPos), node));
        }
        if (WindowManager::collisionSystem->checkMovements(node->pos.x, node->pos.y, DOWN)) {
            neighbors.push_back(new Node(Position(node->pos.x, node->pos.y + 1), DOWN, node->g + 1, manhattanDistance(Position(node->pos.x, node->pos.y + 1), pacmanPos), node));
        }

        return neighbors;
    }
    
    std::vector<Node*> Tree::getPathToBase(const Position& ghostPos, const Position& basePosition) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
        static bool visitedLocation[26][24] = {}; // Initialisation statique, si nécessaire
        
        priorityQueue.push(new Node(ghostPos, NONE, 0, Tree::manhattanDistance(ghostPos, basePosition)));
        visitedLocation[ghostPos.x][ghostPos.y] = true;

        Node* goalNode = nullptr;

        // Boucle principale de l'algorithme A*
        while (!priorityQueue.empty()) {
            Node* currentNode = priorityQueue.top();
            priorityQueue.pop();

            if (currentNode->pos.x == basePosition.x && currentNode->pos.y == basePosition.y) {
                goalNode = currentNode;
                break;
            }

            std::vector<Node*> neighbors = Tree::generateNeighborsForBlinkyPath(currentNode, basePosition);
            for (Node* neighbor : neighbors) {
                if (!visitedLocation[neighbor->pos.x][neighbor->pos.y]) {
                    priorityQueue.push(neighbor);
                    visitedLocation[neighbor->pos.x][neighbor->pos.y] = true;
                }
            }
        }

        std::vector<Node*> path;

        if (goalNode != nullptr) {
            path = Tree::getPath(goalNode);
        } else {
            std::cout << "Aucun chemin trouvé vers la base." << std::endl;
        }

        // Libération de la mémoire
        while (!priorityQueue.empty()) {
            delete priorityQueue.top();
            priorityQueue.pop();
        }

        memset(visitedLocation, 0, sizeof(visitedLocation));

        return path;
    }

    // Fonction pour obtenir le chemin à partir d'un nœud but
    std::vector<Node*> Tree::getPath(Node* goalNode) {
        std::vector<Node*> pathToPacman;

        Node* currentNode = goalNode;
        while (currentNode != nullptr) {
            pathToPacman.push_back(currentNode);
            currentNode = currentNode->parent;
        }

        std::reverse(pathToPacman.begin(), pathToPacman.end());

        return pathToPacman;
    }

} // namespace GameEngine
