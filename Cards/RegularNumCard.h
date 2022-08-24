//
// Created by יובל קרן on 8/17/2022.
//

#ifndef MAIN_CPP_REGULARNUMCARD_H
#define MAIN_CPP_REGULARNUMCARD_H

#include "card.h"

class RegularNumCard : public Card {
public:
    RegularNumCard(int value, CardShape cardShape) : Card(value, cardShape) {};
    std::string getCardFullNameAsString() const override;
private:

};


#endif //MAIN_CPP_REGULARNUMCARD_H
