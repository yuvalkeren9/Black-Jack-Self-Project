//
// Created by יובל קרן on 8/14/2022.
//

#include "Bank.h"
#include <stdexcept>
#include <exception>

using namespace std;


class Bank::notEnoughMoney : public std::exception {
public:
    notEnoughMoney() = default;
    const char *what() const noexcept override {
        return "Not enough money to complete this transaction";
    }
};


void Bank::addMoney(const std::string &playerName, int moneyToAdd) {
    listOfParticipants[playerName] += moneyToAdd;
}

void Bank::addPlayerToBank(const std::string &playerName, int moneyToInit) {
    try{
        while(true) {
            listOfParticipants.at(playerName);
            //TODO: make this orthogonal
            cout << "Player name already in use." << endl;
        }
    }
    catch (const std::out_of_range& e){
        listOfParticipants[playerName] += moneyToInit;
    }
}

void Bank::decreaseMoney(const std::string &playerName, int moneyToADecrease) {
    if (listOfParticipants[playerName] - moneyToADecrease < 0){
        throw Bank::notEnoughMoney();
    }
    else{
        listOfParticipants[playerName] -= moneyToADecrease;
    }
}

int Bank::getPlayersMoney(const string &playerName) const {
    return listOfParticipants.at(playerName);
}

void Bank::printDetails() const {
    for (const auto & player : listOfParticipants){
        cout << player.first << " has a total of " << player.second << " money" << endl;
    }

}

void Bank::removePlayerFromBank(const string &playerName) {
    listOfParticipants.erase(playerName);
}



