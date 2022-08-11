//
// Created by יובל קרן on 8/8/2022.
//

#include <iostream>
#include "RealPlayer.h"

Action RealPlayer::chooseAction() const {
    int move;
    std::cout << "Choose your move:" << std::endl <<"press 0 for hit, 1 for stand";
    std::cin >> move;
    return static_cast<Action>(move);
}
