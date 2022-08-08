//
// Created by יובל קרן on 8/5/2022.
//

#include <iostream>
#include "AceCard.h"
#include <cassert>

void AceCard::changeAceValue() {
    assert(this->getValue() == 1 || this->getValue() == 11);
    switch(getValue()){
        case 1:
            is1 = false;
            value = 11;
            break;
        case 11:
            is1 = true;
            value =1;
            break;
        default:
            std::cerr << "something has gone very wrong! The value of the card is:" <<this->getValue() << std::endl;
            break;
    }
}
