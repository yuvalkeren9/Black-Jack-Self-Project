//
// Created by יובל קרן on 8/17/2022.
//

#include "RegularNumCard.h"
#include <string>

using namespace std;

//TODO: delete when finished
//void RegularNumCard::setTexture() {
//    string cardShapeString = getCardShapeAsString();
//    string startOfFileText = "../GUIfiles/Sprites/Cards/card";
//    string cardValue = to_string(getValue());
//    string pngEnding = ".png";
//    string fileName = (startOfFileText + cardShapeString + cardValue + pngEnding);
//    cardTexture.loadFromFile(fileName);
//}


std::string RegularNumCard::getCardFullNameAsString() const {
    return (getCardShapeAsString() + to_string(getValue()));
}
