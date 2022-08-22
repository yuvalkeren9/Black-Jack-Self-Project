//
// Created by יובל קרן on 8/5/2022.
//

#include "card.h"
#include <fstream>
#include <iostream>

using namespace std;

class Card::intToCardTypeError : public std::exception {
private:
    int value;
public:
    explicit intToCardTypeError(int value) : std::exception(), value(value) {};
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
            throw Card::intToCardTypeError(value);
    }
}

void Card::print(std::ostream& os) const{
    os << "The value of the card is:" << this->value <<std::endl;
}

int Card::getValue() const {
    return value;
}


string Card::getCardShapeAsString() {
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
            cout << "Shit I messed something up" << endl;
            break;
    }
    return cardShapeString;
}

const sf::Texture & Card::getTexture() const {
    return cardTexture;
}


string createStringForCardTypeSprite(Card& card){
    string cardShapeString = card.getCardShapeAsString();
    string startOfFileText = "../Sprites/Cards/card";
    string cardValue = to_string(card.getValue());
    string pngEnding = ".png";
    return (startOfFileText + cardShapeString + cardValue + pngEnding);
}


