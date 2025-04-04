#pragma once
#include "config.hpp"

namespace GameEngine {

    struct Position {
        int x;
        int y;
        Position(int _x, int _y) : x(_x), y(_y) {}
    };

    struct Node {
        Position pos;  
        int direction;
        int g;
        int h;
        Node* parent;
        Node(Position pos1, int dir, int cost, int heuristic, Node* par = nullptr): pos(pos1), direction(dir), g(cost), h(heuristic), parent(par) {}
        int f() const { return g + h; }
    };

    struct CompareNodes {
        bool operator()(Node* lhs, Node* rhs) const {
            return lhs->f() > rhs->f(); // Tri par f croissant pour A*
        }
    };

    

    class CollisionSystem; // Forward declaration

    class Tree {

        enum {
            NONE = -1,
            LEFT = 0,
            RIGHT = 1,
            UP = 2,
            DOWN = 3
        };
        
        public:

            static std::vector<Node*> getPathBlinkyToPacman(const Position& blinkyPosition, const Position& pacmanPosition);

            static std::vector<Node*> getPathPinkyToPacman(const Position& pinkyPos, const Position& pacmanPos, int direction);

            static std::vector<Node*> getPathInkyToPacman(const Position& inkyPosition, const Position& pacmanPosition, const Position& blinkyPosition, int direction);

            static std::vector<Node*> getPathToBase(const Position& ghostPos, const Position& basePosition);

            static int manhattanDistance(const Position& a, const Position& b);

            static std::vector<Node*> generateNeighborsForBlinkyPath(Node* node,const Position& pacmanPos);

            static Node* goalNode;

            static std::vector<Node*> getPath(Node* goalNode1);
            
    };

} // namespace GameEngine
