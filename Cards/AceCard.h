//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_ACECARD_H
#define CARDGAME_ACECARD_H

#include "card.h"

class AceCard : public Card {
private:
    bool is11;
    void setImage();


public:
    explicit AceCard(const CardShape& cardShape) : Card(11, cardShape), is11(true) {
        setImage();
    };
    void changeAceValue();
};



#endif //CARDGAME_ACECARD_H
