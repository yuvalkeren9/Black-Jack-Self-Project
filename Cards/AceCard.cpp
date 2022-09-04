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

string AceCard::getCardFullNameAsString() const {
    return (getCardShapeAsString() + "A");

}


