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

queue<std::unique_ptr<Card>> createRegularCardDeck(int numOfDecks){
    static int smallestCardValue = 2;
    static int largestCardValue = 10;
    static int diffrentCardTypes = 4;

    vector<unique_ptr<Card>> tempVector;
    queue<unique_ptr<Card>> tempQueue;

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
        for(auto& card : tempVector){
            tempQueue.push(std::move(card));
        }
    }
    return tempQueue;
}

System::System(std::queue<std::unique_ptr<Card>> deck, int numOfPlayers) : cardDeck(std::move(deck)), PlayersVector(), dealer("Dealer") {
    //TODO: make a function that does this, that creates names for AI and lets user select his name
    PlayersVector.push_back(unique_ptr<Player> (new RealPlayer("Aang")));
    for (int i=1 ; i < numOfPlayers; ++i){
        PlayersVector.push_back(unique_ptr<Player> (new AIPlayer("Azula")));
    }
    dealStartingCards();
}

void System::printPlayerHands() const {
    for(const auto& player : this->PlayersVector){
        cout << "Player: " << *player << endl;
        player->printHand();
        cout << "The sum of the player is:" << player->getCurrentHandSum() << endl << endl;
    }
    cout << "Player: " << dealer << endl;
    dealer.printHand();
    cout << "The sum of the dealer is:" << dealer.getCurrentHandSum() << endl << endl;
}

void System::dealStartingCards() {
    static int numOfStartingCards = 2;
    for (auto& player: this->PlayersVector){
        for(int i=0; i < numOfStartingCards; ++i) {
            hitAPlayer(player.get());
        }
    }
    for (int i =0; i < numOfStartingCards; ++i){
        //TODO: hit dealer function to replace following code
        dealer.hit(this->cardDeck.front().get());
        moveFirstCardToEndOfDeck();
    }

}

void System::moveFirstCardToEndOfDeck() {
    unique_ptr<Card> temp = move(this->cardDeck.front());
    this->cardDeck.pop();
    this->cardDeck.push(move(temp));
}

void System::playRound() {
    if(checkDealerForNaturalBlackJack()){
        return;
    }
    for (auto& player: this->PlayersVector){
        while(makeMove(player.get()));     //makeMove returns false when player decides to stand or is over 21
    }
    playDealerTurn();
    playResults();
}

bool System::checkPlayerForNaturalBlackJack(Player *&player) {
    if(player->getCurrentHandSum() == blackJackWinnerNum){
        //TODO : exit round, win 1.5 money
        cout << "Player" << *player << "has a Natural BlackJack!" << endl;
        return true;
    }
    return false;
}

bool System::checkDealerForNaturalBlackJack() {
    if(dealer.getCurrentHandSum() == blackJackWinnerNum){
        cout << "Player" << dealer << "has a BlackJack!" << endl;
        //TODO: make everybody lose money, end round
        return true;
    }
    else {
        return false;
    }
}

void System::hitAPlayer(Player* player) {
    player->hit(this->cardDeck.front().get());   //giving the player a regular C pointer of a card
    moveFirstCardToEndOfDeck();
}

bool System::makeMove(Player* player){
    if(checkPlayerForNaturalBlackJack(player)){
        return false;
    }
    Action action = player->chooseAction();
        switch(static_cast<int>(action)){
            case 0:
                cout<< "hitting player..." << *player << endl;
                hitAPlayer(player);
                if(player->getCurrentHandSum() > 21) {
                    cout << "Youre over 21, youre out!!" << endl;
                    return false;
                }
                else {
                    //TODO: print the actual card
                    cout << "your current sum is:" << player->getCurrentHandSum() << endl;
                    return true;
                }
            case 1:
                cout<< "the following player decided to stand" << *player << endl;
                return false;
            default:
                cout << " shit man something has gone way way wrong";
                //TODO : crash the program
                return false;
        }
}

void System::playDealerTurn() {
    const static int dealerDefaultStandValue = 17;
    Player* tempPtrToDealer = &dealer;
    while (dealer.getCurrentHandSum() < dealerDefaultStandValue){
        hitAPlayer(tempPtrToDealer);
    }
}

void System::playResults() {
    int dealerSum = dealer.getCurrentHandSum();
    if (dealerSum > blackJackWinnerNum){               //dealer has a bust
        endOfRoundDealerBust();
        return;
    }
    for (auto& player : this->PlayersVector){
        int currentPlayerSum = player->getCurrentHandSum();
        if(currentPlayerSum > blackJackWinnerNum) {
            endOfRoundPlayerBust(player->getName());
            continue;
        }
        if (dealerSum == currentPlayerSum ){
            //TODO : return bet sum, nothing happens
            cout << "Player " << *player << " is tied with the dealer!" << endl;
            continue;
        }
        if (dealerSum > currentPlayerSum){
            //TODO: make player lose bet
            cout << "Player " << *player << " has lost to the dealer!" << endl;
            continue;
        }
        else{                                     //player's sum is higher than dealer's
            //TODO: have player win money
            cout << "Player " << *player << " beat the dealer!" << endl;
            continue;
        }
    }
}


/** dealer related functions */
void System::endOfRoundDealerBust(){
    for (auto& player : this->PlayersVector){
        if(player->getCurrentHandSum() <= blackJackWinnerNum){ //player did not bust
            //TODO: add moneyyyy
        }
    }
}

void System::endOfRoundPlayerBust(const string& playerName) {
    cout << playerName << " has a bust! He loses" << endl;
    //TODO: make player lose money

}

