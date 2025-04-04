#include "headers/Map.hpp"

namespace GameEngine {

    int lvl1[26][24] = {
      // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 
        {3,6,6,6,6,6,6,6,6,6,6,2,3,6,6,6,6,6,6,6,6,6,6,2}, //0
        {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1}, //1
        {1,0,3,6,2,0,3,6,6,2,0,1,1,0,3,6,6,2,0,3,6,2,0,1}, //2
        {1,0,1,8,1,0,1,8,8,1,0,1,1,0,1,8,8,1,0,1,8,1,0,1}, //3
        {1,0,5,6,4,0,5,6,6,4,0,5,4,0,5,6,6,4,0,5,6,4,0,1}, //4
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //5
        {1,0,3,6,2,0,3,2,0,3,6,6,6,6,2,0,3,2,0,3,6,2,0,1}, //6
        {1,0,5,6,4,0,1,1,0,5,6,2,3,6,4,0,1,1,0,5,6,4,0,1}, //7
        {1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1}, //8
        {1,0,0,0,0,0,1,5,6,2,0,1,1,0,3,6,4,1,0,0,0,0,0,1}, //9
        {5,6,6,6,2,0,1,3,6,4,0,5,4,0,5,6,2,1,0,3,6,6,6,4}, //10
        {8,8,8,8,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,8,8,8,8}, //11
        {8,8,8,8,1,0,1,1,0,3,9,9,9,9,2,0,1,1,0,1,8,8,8,8}, //12
        {6,6,6,6,4,0,5,4,0,1,8,8,8,8,1,0,5,4,0,5,6,6,6,6}, //13
        {0,0,0,0,0,0,0,0,0,1,8,8,8,8,1,0,0,0,0,0,0,0,0,0}, //14
        {6,6,6,6,2,0,3,2,0,1,8,8,8,8,1,0,3,2,0,3,6,6,6,6}, //15
        {8,8,8,8,1,0,1,1,0,5,6,6,6,6,4,0,1,1,0,1,8,8,8,8}, //16
        {8,8,8,8,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,8,8,8,8}, //17
        {3,6,6,6,4,0,5,4,0,3,6,6,6,6,2,0,5,4,0,5,6,6,6,2}, //18
        {1,0,0,0,0,0,0,0,0,5,6,2,3,6,4,0,0,0,0,0,0,0,0,1}, //19
        {1,0,0,3,6,2,0,0,0,0,0,1,1,0,0,0,0,0,3,6,2,0,0,1}, //20
        {1,0,0,5,2,1,0,3,6,2,0,1,1,0,3,6,2,0,1,3,4,0,0,1}, //21
        {5,2,0,0,1,1,0,1,8,1,0,5,4,0,1,8,1,0,1,1,0,0,3,4}, //22
        {3,4,0,0,5,4,0,5,6,4,0,0,0,0,5,6,4,0,5,4,0,0,5,2}, //23
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //24
        {5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4}  //25
    };    

    // 11 12
    // 12 12

    Map::Map(){

        this->fontsLoader = new FontsLoader("Score : ", 20, this->fontRect);

        this->fontsLoader->setPosToText(5, 550);

        this->hTile = TextureLoader::getPlayerTexture("assets/map/hTile.png");
        this->vTile = TextureLoader::getPlayerTexture("assets/map/vTile.png");
        this->curveDownLeft = TextureLoader::getPlayerTexture("assets/map/curveBottomLeft.png");
        this->curveDownRight = TextureLoader::getPlayerTexture("assets/map/curveBottomRIght.png");
        this->curveUpLeft = TextureLoader::getPlayerTexture("assets/map/curveHighLeft.png");
        this->curveUpRight = TextureLoader::getPlayerTexture("assets/map/curveHighRight.png");
        this->blackTile = TextureLoader::getPlayerTexture("assets/map/blackTile.png");
        this->candy = TextureLoader::getPlayerTexture("assets/candy/candy.png");
        this->cherryTile = TextureLoader::getPlayerTexture("assets/candy/cherry.png");

        this->allText.push_back(hTile);
        this->allText.push_back(vTile);
        this->allText.push_back(curveUpLeft);
        this->allText.push_back(curveUpRight);
        this->allText.push_back(curveDownLeft);
        this->allText.push_back(curveDownRight);
        this->allText.push_back(candy);
        this->allText.push_back(cherryTile);

        this->loadMap(lvl1);

        this->setCandyIntoTheMap();

        this->setCherryIntoTheMap();

        this->src.x = this->src.y = 0;
        this->src.w = this->dest.w = 20;
        this->src.h = this->dest.h = 20;

        this->dest.x = this->dest.y = 0;

        this->mapEtat = IDLE;

    }

    void Map::setPlayer(Pacman* joueur){
        this->player = joueur;
    }

    void Map::setMessageToFonts() {

        std::string message = "Score = " + std::to_string(player->getScore());

        this->fontsLoader->setMessage(message.c_str());
    }

    void Map::loadMap(int arr[26][24]){
        for(int row = 0; row < 26; row++){
            for(int col = 0; col < 24; col++){
                this->map[row][col] = arr[row][col];
            }
        }
    }

    void Map::setCandyIntoTheMap() {

        while(this->checkNbCandyInMap() < maxCandy) {
            int* pos = Math::getRandomPos();
            int col = pos[0];
            int row = pos[1];
            if(map[row][col] == 0) {
                map[row][col] = CANDY_TILE;
            }
            delete[] pos;
        }
    }

    int Map::checkNbCandyInMap(){
        int compteur = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 24; ++j) {
                if (this->map[i][j] == 7) {
                    compteur++;
                }
            }
        }
        return compteur;
    }

    void Map::setCherryIntoTheMap(){
        while(this->checkNbCherryInMap() < maxCherry) {
            int* pos = Math::getRandomPos();
            int col = pos[0];
            int row = pos[1];
            if(map[row][col] == 0) {
                map[row][col] = CHERRY_TILE;
            }
            delete[] pos;
        }
    }

    int Map::checkNbCherryInMap(){
        int compteur = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 24; ++j) {
                if (this->map[i][j] == 10) {
                    compteur++;
                }
            }
        }
        std::cout << "Nb cherry : " << compteur << "\n";
        return compteur;
    }




    Map::~Map(){
        for (unsigned int i = 0; i < allText.size(); i++)
        {
            SDL_DestroyTexture(allText[i]);
        }
        this->fontsLoader->~FontsLoader();
        player = nullptr;
    }

    void Map::drawMap(){
        
        int type = 0;

        for(int row = 0; row < 26; row++){
            for(int col = 0; col < 24; col++){
                type = map[row][col];
                dest.x = col * 20;
                dest.y = row * 20;
                switch (type)
                {
                case H_TILE:
                    TextureLoader::draw(hTile, src, dest);
                    break;
                case V_TILE:
                    TextureLoader::draw(vTile, src, dest);
                    break;
                case CURVED_DOWN_LEFT:
                    TextureLoader::draw(curveDownLeft, src, dest);
                    break;
                case CURVED_DOWN_RIGHT:
                    TextureLoader::draw(curveDownRight, src, dest);
                    break;
                case CURVED_UP_RIGHT:
                    TextureLoader::draw(curveUpRight, src, dest);
                    break;
                case CURVED_UP_LEFT:
                    TextureLoader::draw(curveUpLeft, src, dest);
                    break;
                case BLACK_TILE:
                    break;
                case CANDY_TILE:
                    TextureLoader::draw(candy, src, dest);
                    break;
                case VOID_TILE:
                    break;
                case CHANGING_TILE:
                    if((col == 10 && row == 12) || (col == 11 && row == 12) || (col == 12 && row == 12) || (col == 13 && row == 12)) {
                        if(mapEtat == CHASING) {
                            TextureLoader::draw(blackTile, src, dest);
                        } else {
                            TextureLoader::draw(hTile, src, dest);
                        }
                    }
                    break;
                case CHERRY_TILE:
                    TextureLoader::draw(cherryTile, src, dest);
                    break;
                break;
                default:
                    break;
                }
            }
        }
        fontsLoader->drawFont();
    }

    void Map::update(){
        if(this->player != nullptr) {
            this->setMessageToFonts();
        }
    }

    int (*Map::getMap())[24] {
        // Retourne un pointeur vers le tableau map
        return this->map;
    }

} 