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
    CardShape type;

protected:
    int value;
public:
    virtual void print(std::ostream& os) const;
    Card(int value, CardShape type) : value(value), type(type) {};
    virtual ~Card() = default;
    class intToCardTypeError;
    int getValue() const;
};
CardShape intToCardTypeAdapter(int value);


#endif //CARDGAME_CARD_H
