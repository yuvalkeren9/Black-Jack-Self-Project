//
// Created by יובל קרן on 8/14/2022.
//

#ifndef MAIN_CPP_BANK_H
#define MAIN_CPP_BANK_H

#include <iostream>
#include <unordered_map>
#include "../Players/Player.h"

/**
 * Class that handles everything related to the bets in the game.
 */
class Bank {
private:
    std::unordered_map<std::string, int> listOfParticipants;

public:
    /**
     * Adds a player to the bank. Function th
     * @param playerName The name of the player
     * @param moneyToInit Amount of money to give the player
     */
    void addPlayerToBank(const std::string &playerName, int moneyToInit = 1000);

    /**
     *
     * @param playerName
     * @param moneyToAdd
     */
    void addMoney(const std::string &playerName, int moneyToAdd);
    void decreaseMoney(const std::string &playerName, int moneyToADecrease);
    void removePlayerFromBank(const std::string&playerName);
    int getPlayersMoney(const std::string& playerName) const;
    class notEnoughMoney;
    void printDetails() const;
};


#endif //MAIN_CPP_BANK_H
