//
// Created by יובל קרן on 8/8/2022.
//

#ifndef MAIN_CPP_REALPLAYER_H
#define MAIN_CPP_REALPLAYER_H

#include "Player.h"

#include <utility>

class RealPlayer : public Player {
private:



public:
    explicit RealPlayer(std::string name, long int startingMoney = 1000) : Player(std::move(name)){};


};


#endif //MAIN_CPP_REALPLAYER_H
