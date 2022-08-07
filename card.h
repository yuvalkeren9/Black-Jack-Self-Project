//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_CARD_H
#define CARDGAME_CARD_H

#include <queue>
#include <cstdlib>
#include <memory>


enum CardShape {Clubs, Diamonds, Hearts, Spades };

class Card {
private:
    int value;
    CardShape type;


public:
    virtual void print(std::ostream& os) const;
    Card(int value, CardShape type) : value(value), type(type) {};
    virtual ~Card() = default;
    class intToCardTypeError;
};
CardShape intToCardTypeAdapter(int value);


#endif //CARDGAME_CARD_H
