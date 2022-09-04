//
// Created by יובל קרן on 8/5/2022.
//

#include "card.h"
#include <iostream>

using namespace std;

class Card::intToCardTypeError : public std::exception {
public:
    explicit intToCardTypeError() : std::exception(){};
    const char *what() const noexcept override {
        return "Illegal number - no possible card type conversion";
    }
};

CardShape intToCardTypeAdapter(int value) {
    switch (value){
        case 1:
            return Clubs;
        case 2:
            return Diamonds;
        case 3:
            return Hearts;
        case 4:
            return Spades;
        default:
            throw Card::intToCardTypeError();
    }
}

void Card::print(std::ostream& os) const{
    os << "The value of the card is:" << this->value <<std::endl;
}

int Card::getValue() const {
    return value;
}


string Card::getCardShapeAsString() const {
    string cardShapeString;
    switch (static_cast<CardShape> (this->type)){
        case 0:
            cardShapeString = "Clubs";
            break;
        case 1:
            cardShapeString = "Diamonds";
            break;
        case 2:
            cardShapeString = "Hearts";
            break;
        case 3:
            cardShapeString = "Spades";
            break;
        default:
            cout << "Damn I messed something up" << endl;
            break;
    }
    return cardShapeString;
}
