//
// Created by יובל קרן on 8/8/2022.
//

#ifndef MAIN_CPP_AIPLAYER_H
#define MAIN_CPP_AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player{
public:
    explicit AIPlayer(std::string name, long int startingMoney = 1000) : Player(std::move(name)){};
    Action chooseAction() const override;
};


#endif //MAIN_CPP_AIPLAYER_H
