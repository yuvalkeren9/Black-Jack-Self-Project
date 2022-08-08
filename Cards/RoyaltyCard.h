//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_ROYALTYCARD_H
#define CARDGAME_ROYALTYCARD_H

#include "card.h"

enum RoyaltyType {Jack, Queen, King};
class RoyaltyCard : public Card {
private:
    RoyaltyType royaltyType;

public:
    RoyaltyCard(CardShape cardShape, RoyaltyType royaltyType) : Card(10, cardShape), royaltyType(royaltyType) {};

};


#endif //CARDGAME_ROYALTYCARD_H
