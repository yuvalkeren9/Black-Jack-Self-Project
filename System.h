//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_SYSTEM_H
#define CARDGAME_SYSTEM_H

#include "Cards/card.h"
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <utility>
#include "Players/Player.h"



class System {
private:
    std::vector<std::unique_ptr<Card>> cardDeck;
    std::vector<std::unique_ptr<Player>> PlayersVector;
    std::vector<Card*> dealerHand;
public:
//    void printCards() const{
//        for(const std::unique_ptr<Card>& cards : cardDeck){
//            cards->print(std::cout);
//        }
//    }
    /** Constructor for the System class. Doesn't create its own deck so that any sort of and amount of cards can be played. */
    explicit System(std::vector<std::unique_ptr<Card>> deck, int numOfPlayers);
    void dealStartingCards();





    //for testing
    void printPlayerHands() const;

};



/**
 * Function that generates a regular card deck.
 * @param numOfDecks - how many "regular" decks to be created in the deck (some casinos play BlackJack with 3 decks)
 * @return shuffled card deck
 */
std::vector<std::unique_ptr<Card>> createRegularCardDeck(int numOfDecks);


#endif //CARDGAME_SYSTEM_H
