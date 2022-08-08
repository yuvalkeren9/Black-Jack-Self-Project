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

long int Player::getCurrentHandSum() {
    long int sum =0;
    for (const auto& card : this->m_playerHand ){
        sum += card->getValue();
    }
    return sum;
}

void Player::hit(Card* newCard) {
    addToDeck(newCard);
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
    std::cout << this->m_name << std::endl;
}

void Player::printHand() const {
    for(const auto& card : this->m_playerHand){
        card->print(std::cout);
    }
}
