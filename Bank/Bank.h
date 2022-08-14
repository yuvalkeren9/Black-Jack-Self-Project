//
// Created by יובל קרן on 8/14/2022.
//

#ifndef MAIN_CPP_BANK_H
#define MAIN_CPP_BANK_H

#include <iostream>
#include <unordered_map>
#include "../Players/Player.h"

class Bank {
private:
    std::unordered_map<std::string, int> listOfParticipants;


public:
    void addPlayerToBank(const std::string &playerName, int moneyToInit = 1000);
    void addMoney(const std::string &playerName, int moneyToAdd);
    void decreaseMoney(const std::string &playerName, int moneyToADecrease);
    int getPlayersMoney(const std::string& playerName) const;
    class notEnoughMoney;
    void printDetails() const;
};


#endif //MAIN_CPP_BANK_H
