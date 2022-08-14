//
// Created by יובל קרן on 8/8/2022.
//

#include <cassert>
#include <iostream>
#include "Player.h"
#include "../Cards/AceCard.h"

void Player::addToDeck(Card* newCard) {
    this->m_playerHand.push_back(newCard);
}

void Player::updateAces() {
    int sum =0;
    /** first we calculate al the cards that are not aces. Then, we calculate the different possibilities that the aces raise */
    for (const auto& card : this->m_playerHand ){
        int currentValue = card->getValue();
        if (currentValue == sizeOfHigherValueAce)
            continue;
        sum += currentValue;
    }
    for (const auto& card : this->m_playerHand ){
        int currentValue = card->getValue();
        if (currentValue == sizeOfHigherValueAce){
            if(sum + currentValue > 21) {
                changeAceFromElevenToOne();
                sum += 1;
            }
            else
                sum += 11;
        }
    }
}

int Player::getCurrentHandSum() const {
    int sum = 0;
    for (const auto& card : this->m_playerHand ){
        sum += card->getValue();
    }
    return sum;
}


void Player::hit(Card* newCard) {
    addToDeck(newCard);
    updateAces();
}

void Player::changeAceFromOneToEleven() {
    assert(!m_playerHand.empty());
    for(auto& card : this->m_playerHand){
        if (card->getValue() == 1){
            dynamic_cast<AceCard*>(card)->changeAceValue();
            break;
        }
    }
}

void Player::changeAceFromElevenToOne() {
    assert(!m_playerHand.empty());
    for(auto& card : this->m_playerHand){
        if (card->getValue() == 11){
            dynamic_cast<AceCard*>(card)->changeAceValue();
            break;
        }
    }
}

void Player::print() const {
    std::cout << this->m_name;
}

void Player::printHand() const {
    for(const auto& card : this->m_playerHand){
        card->print(std::cout);
    }
}

std::string Player::getName() const {
    return m_name;
}

void Player::emptyDeck() {
    while (!m_playerHand.empty()){
        m_playerHand.pop_back();
    }
}


std::ostream& operator<<(std::ostream& os, const Player& player){
    player.print();
    return os;
}