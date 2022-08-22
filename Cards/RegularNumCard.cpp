//
// Created by יובל קרן on 8/17/2022.
//

#include "RegularNumCard.h"
#include <string>
#include <iostream>

using namespace std;


void RegularNumCard::setTexture() {
    string cardShapeString = getCardShapeAsString();
    string startOfFileText = "../GUIfiles/Sprites/Cards/card";
    string cardValue = to_string(getValue());
    string pngEnding = ".png";
    string fileName = (startOfFileText + cardShapeString + cardValue + pngEnding);
    cardTexture.loadFromFile(fileName);
}
