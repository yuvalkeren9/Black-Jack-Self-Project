//
// Created by יובל קרן on 8/8/2022.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H
#include <utility>

#include "../Cards/card.h"

enum Action {Hit, Stand};
class Player {
private:
    std::vector<Card*> m_playerHand;
    std::string m_name;
    long int m_money;


public:
    explicit Player(std::string name, long int startingMoney = 1000) : m_playerHand(), m_name(std::move(name)), m_money(startingMoney) {};
    virtual ~Player() = default;
    void addToDeck(Card* newCard);
    int getCurrentHandSum() const;
    void print() const;
    void printHand() const;

    void updateAces();
    std::string getName() const;



    virtual Action chooseAction() const = 0;
    /** Game Moves */
    void hit(Card* newCard);
    void changeAceFromOneToEleven();
    void changeAceFromElevenToOne();



};

std::ostream& operator<<(std::ostream& os, const Player& player);

#endif //MAIN_CPP_PLAYER_H
