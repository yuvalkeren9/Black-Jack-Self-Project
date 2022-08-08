//
// Created by יובל קרן on 8/5/2022.
//

#include "System.h"


#include "Cards/card.h"
#include <fstream>
#include <memory>
#include "Cards/RoyaltyCard.h"
#include "Cards/AceCard.h"
#include<random>
#include <algorithm>
#include <chrono>
#include <cassert>
#include "Players/RealPlayer.h"
#include "Players/AIPlayer.h"


using namespace std;

vector<std::unique_ptr<Card>> createRegularCardDeck(int numOfDecks){
    static int smallestCardValue = 2;
    static int largestCardValue = 10;
    static int diffrentCardTypes = 4;

    vector<unique_ptr<Card>> tempVector;

    assert(numOfDecks > 0);
    for (int i=0; i < numOfDecks; ++i){                 //creating the 2-10 regular cards
        for(int j=smallestCardValue; j <= largestCardValue; ++j){
            for (int p = 1; p <= diffrentCardTypes; ++p) {
                tempVector.push_back(make_unique<Card> (j, intToCardTypeAdapter(p)));
            }
        }               //the royal house is seperated from the regular cards because I wanted to experiment with make unique

        for (int p = 1; p <= diffrentCardTypes; ++p) {
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), Jack)));
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), Queen)));
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), King)));
            tempVector.push_back(unique_ptr<Card> (new AceCard(intToCardTypeAdapter(p))));
        }
        unsigned num = chrono::system_clock::now().time_since_epoch().count();    //generating a random number for shuffle function
        shuffle(tempVector.begin(), tempVector.end(), default_random_engine(num));
    }
    return tempVector;
}

System::System(std::vector<std::unique_ptr<Card>> deck, int numOfPlayers) : cardDeck(std::move(deck)), PlayersVector(), dealerHand() {
    //TODO: make a function that does this, that creates names for AI and lets user select his name
    PlayersVector.push_back(unique_ptr<Player> (new RealPlayer("Aang")));
    for (int i=1 ; i < numOfPlayers; ++i){
        PlayersVector.push_back(unique_ptr<Player> (new AIPlayer("Azula")));
    }
    dealStartingCards();
}

void System::printPlayerHands() const {
    //TODO edit all the printing functions, remmeber this was just for testing
    for(const auto& player : this->PlayersVector){
        cout << "Player: "; player->print();
        player->printHand(); cout <<endl;
    }
}

void System::dealStartingCards() {
    //TODO: Make a function that moves the first card to the bottom, it will look something like the code below
    for (auto& player : this->PlayersVector){
        unique_ptr<Card> temp = std::move(this->cardDeck[0]);
        this->cardDeck.erase(cardDeck.begin());
        player->hit(temp.get());
        cardDeck.push_back(std::move(temp));
        temp = std::move(this->cardDeck[0]);
        this->cardDeck.erase(cardDeck.begin());
        player->hit(temp.get());
        cardDeck.push_back(std::move(temp));
    }
}
