//
// Created by יובל קרן on 8/5/2022.
//

#include "RoyaltyCard.h"
#include <iostream>

using namespace std;

void RoyaltyCard::setImage() {
    string cardShapeString = getCardShapeAsString();
    string startOfFileText = "../GUIfiles/Sprites/Cards/card";
    string cardValue = getCardTypeAsString();
    string pngEnding = ".png";
    string fileName = (startOfFileText + cardShapeString + cardValue + pngEnding);
    cardImage.loadFromFile(fileName);

}

std::string RoyaltyCard::getCardTypeAsString() const {
    string cardTypeString;
    switch (static_cast<RoyaltyType> (royaltyType)) {
        case 0:
            cardTypeString = "J";
            break;
        case 1:
            cardTypeString ="Q";
            break;
        case 2:
            cardTypeString = "K";
            break;
        default:
            cout << "Not again.. BAD BaD BAD;";
            break;
    }
    return cardTypeString;

}
