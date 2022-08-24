//
// Created by יובל קרן on 8/5/2022.
//

#include <iostream>
#include "AceCard.h"
#include <cassert>

using namespace std;

void AceCard::changeAceValue() {
    assert(this->getValue() == 1 || this->getValue() == 11);
    switch(getValue()){
        case 1:
            is11 = true;
            value = 11;
            break;
        case 11:
            is11 = false;
            value =1;
            break;
        default:
            std::cerr << "something has gone very wrong! The value of the card is:" <<this->getValue() << std::endl;
            break;
    }
}


//TODO: delete when project is ready
//void AceCard::setTexture() {
//    string cardShapeString = getCardShapeAsString();
//    string startOfFileText = "../GUIfiles/Sprites/Cards/card";
//    string cardValue = "A";
//    string pngEnding = ".png";
//    string fileName = (startOfFileText + cardShapeString + cardValue + pngEnding);
//    cardTexture.loadFromFile(fileName);
//
//}

string AceCard::getCardFullNameAsString() const {
    return (getCardShapeAsString() + "A");

}


