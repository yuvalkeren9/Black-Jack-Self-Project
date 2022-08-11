//
// Created by יובל קרן on 8/8/2022.
//

#include "AIPlayer.h"


Action AIPlayer::chooseAction() const {
    if (this->getCurrentHandSum() < 16)
        return Hit;
    else
        return Stand;
}
