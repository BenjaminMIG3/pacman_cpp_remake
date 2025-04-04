#include "headers/Math.hpp"

namespace GameEngine {

    /**
     * @static 
     * Cette fonction doit arrondir le resultat de num1/num2 en fonction des marges hautes et basses
     * @param num1 numérateur
     * @param num2 diviseur
     * @param margeHaute marge à partir de laquelle on arrondie au supérieur
     * @param margeBasse marge à partir de laquelle on arrondie à l'inférieur
     */
    int Math::roundByDecimal(int num1, int num2, float margeHaute, float margeBasse){
        if (num2 == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }

        // Calculer le résultat de la division
        float divisionResult = static_cast<float>(num1) / num2;

        // Récupérer la partie entière du résultat
        int integerPart = static_cast<int>(divisionResult);

        // Récupérer la partie décimale
        float decimalPart = divisionResult - integerPart;

        // S'assurer que la partie décimale est positive
        if (decimalPart < 0) {
            decimalPart = -decimalPart;
        }

        std::cout << "Partie décimale : " << decimalPart << std::endl;

        // Arrondir en fonction des marges haute et basse
        if (decimalPart > margeHaute) {
            return integerPart + 1;
        } else if (decimalPart < margeBasse) {
            return integerPart;
        } else {
            return integerPart; // ou une autre logique si nécessaire
        }
    }

    /**
     * Retourne vrai ou faux en random
     * @return bool
     */
    bool Math::pileOrFace() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 1);

        bool result = dis(gen) == 1;
        std::cout << "pileOrFace résultat : " << result << std::endl; // Ajout du débogage
        return result;
    }

    /**
     * Retourne une position aléatoire dans les coordonées de la map
     * 
     */
    int* Math::getRandomPos() {
        int* result = new int[2];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> row(0, 25);
        std::uniform_int_distribution<> col(0, 23);

        result[0] = row(gen);
        result[1] = col(gen);
        return result;
    }

    /**
     * Fonction qui retourne un entier representant une direction à choisir aléatoirement 0 ~ 3
     * @return int direction
     */
    int Math::getRandomDirection(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        int result = dis(gen);
        std::cout << "Direction résultat : " << result << std::endl;
        return result;
    }

    /**
     * Fonction qui retourne un tableau de taille deux répresentant la position que doit atteindre blinky
     */
    int* Math::getHidePositionBlinky(){
        int* result = new int[2];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> row(1, 5);
        std::uniform_int_distribution<> col(1, 5);

        result[0] = row(gen);
        result[1] = col(gen);

        while(WindowManager::map->getMap()[result[0]][result[1]] != 0) {
            result[0] = row(gen);
            result[1] = col(gen);
        }

        std::cout << "Position seek de blinky => [" << result[0] << "][" << result[1] << "]\n";
        return result;
    }

    /**
     * Fonction qui retourne un tableau de taille deux répresentant la position que doit atteindre pinky
     */
    int* Math::getHidePositionPinky(){
        int* result = new int[2];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> row(18, 22);
        std::uniform_int_distribution<> col(1, 5);

        result[0] = row(gen);
        result[1] = col(gen);

        while(WindowManager::map->getMap()[result[0]][result[1]] != 0) {
            result[0] = row(gen);
            result[1] = col(gen);
        }

        std::cout << "Position seek de pinky => [" << result[0] << "][" << result[1] << "]\n";
        return result;
    }

    /**
     * Fonction qui retourne un tableau de taille deux répresentant la position que doit atteindre inky
     */
    int* Math::getHidePositionInky(){
        int* result = new int[2];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> row(17, 22);
        std::uniform_int_distribution<> col(20, 24);

        result[0] = row(gen);
        result[1] = col(gen);

        while(WindowManager::map->getMap()[result[0]][result[1]] != 0) {
            result[0] = row(gen);
            result[1] = col(gen);
        }

        std::cout << "Position seek de inky => [" << result[0] << "][" << result[1] << "]\n";
        return result;
    }
}