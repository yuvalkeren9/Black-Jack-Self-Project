//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_ACECARD_H
#define CARDGAME_ACECARD_H

#include "card.h"

class AceCard : public Card {
private:
    bool is11;


public:
    explicit AceCard(const CardShape& cardShape) : Card(11, cardShape), is11(true) {};
    void changeAceValue();
    std::string getCardFullNameAsString() const override;
};



#endif //CARDGAME_ACECARD_H
