//
// Created by יובל קרן on 8/5/2022.
//

#include "card.h"
#include <fstream>


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
            break;
        case 2:
            return Diamonds;
            break;
        case 3:
            return Hearts;
            break;
        case 4:
            return Spades;
            break;
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

