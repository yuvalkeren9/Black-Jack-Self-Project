//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_ACECARD_H
#define CARDGAME_ACECARD_H

#include "card.h"

class AceCard : public Card {
private:


public:
    explicit AceCard(const CardShape& cardShape) : Card(1, cardShape) {};
};


#endif //CARDGAME_ACECARD_H
