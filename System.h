//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_SYSTEM_H
#define CARDGAME_SYSTEM_H

#include "card.h"
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <utility>



class System {
private:
    std::vector<std::unique_ptr<Card>> cardDeck;
public:
    void printCards() const{
        for(const std::unique_ptr<Card>& cards : cardDeck){
            cards->print(std::cout);
        }
    }
    explicit System(std::vector<std::unique_ptr<Card>> deck) : cardDeck(std::move(deck)) {};
};


std::queue<std::unique_ptr<Card>> createCardDeck(const std::string& fileName);
std::unique_ptr<Card> getPointerToNewCard(const std::string& cardName, const std::string& cardType);
std::vector<std::unique_ptr<Card>> createCardDeck(int numOfDecks);


#endif //CARDGAME_SYSTEM_H
