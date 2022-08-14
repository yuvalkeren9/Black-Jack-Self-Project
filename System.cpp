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
    static int differentCardTypes = 4;

    vector<unique_ptr<Card>> tempVector;
    queue<unique_ptr<Card>> tempQueue;

    assert(numOfDecks > 0);
    for (int i=0; i < numOfDecks; ++i){                 //creating the 2-10 regular cards
        for(int j=smallestCardValue; j <= largestCardValue; ++j){
            for (int p = 1; p <= differentCardTypes; ++p) {
                tempVector.push_back(make_unique<Card> (j, intToCardTypeAdapter(p)));
            }
        }               //the royal house is seperated from the regular cards because I wanted to experiment with make unique

        for (int p = 1; p <= differentCardTypes; ++p) {
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
    createPlayers(numOfPlayers);
    addPlayersToBank();
}

void System::printPlayerHands() const {
    for(const auto& player : this->PlayersVector){
        cout << "Player: " << *player << endl;
        //player->printHand();
        cout << "The sum of the player is:" << player->getCurrentHandSum() << endl << endl;
    }
    cout << "Player: " << dealer << endl;
    //dealer.printHand();
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
        Player* tempDealerPtr = &dealer;
        hitAPlayer(tempDealerPtr);
//        dealer.hit(this->cardDeck.front().get());
//        moveFirstCardToEndOfDeck();
    }

}

void System::moveFirstCardToEndOfDeck() {
    unique_ptr<Card> temp = move(this->cardDeck.front());
    this->cardDeck.pop();
    this->cardDeck.push(move(temp));
}

void System::playRound() {
    dealStartingCards();
    printPlayerHands();
    collectStartingBets();
    printBankDetails();
    if(checkDealerForNaturalBlackJack()){
        return;
    }
    for (auto& player: this->PlayersVector){
        while(makeMove(player.get()));     //makeMove returns false when player decides to stand or is over 21
    }
    playDealerTurn();
    playResults();
    endRound();
}

bool System::checkPlayerForNaturalBlackJack(Player *&player) {
    if(player->getCurrentHandSum() == blackJackWinnerNum){
        processBet(player->getName(), naturalBlackjack);
        cout << "Player" << *player << "has a Natural BlackJack!" << endl;
        return true;
    }
    return false;
}

bool System::checkDealerForNaturalBlackJack() {
    if(dealer.getCurrentHandSum() == blackJackWinnerNum){
        cout << "Player" << dealer << "has a BlackJack!" << endl;
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
                cout << "shit man something has gone way way wrong";
                exit(0);
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
        const string currentPlayerName = player->getName();
        int currentPlayerSum = player->getCurrentHandSum();
        if(currentPlayerSum > blackJackWinnerNum) {
            endOfRoundPlayerBust(currentPlayerName);
            continue;
        }
        if (dealerSum == currentPlayerSum ){
            processBet(currentPlayerName, tie);
            cout << "Player " << *player << " is tied with the dealer!" << endl;
            continue;
        }
        if (dealerSum > currentPlayerSum){
            cout << "Player " << *player << " has lost to the dealer!" << endl;
            continue;
        }
        else{                                     //player's sum is higher than dealer's
            processBet(currentPlayerName, regular);
            cout << "Player " << *player << " beat the dealer!" << endl;
            continue;
        }
    }
}

/** Bank related functions */
void System::addPlayersToBank(){
    for (const auto& player : PlayersVector){
        bank.addPlayerToBank(player->getName());
    }
}

void System::collectStartingBets() {
    for (auto& player : PlayersVector){
        int currentPlayersMoney = bank.getPlayersMoney(player->getName());
        const string currentPlayerName = player->getName();
        assert(currentPlayersMoney != 0);
        if(currentPlayersMoney < startingBet){
            currentRoundBetsMap[currentPlayerName] = currentPlayersMoney;
            bank.decreaseMoney(currentPlayerName, currentPlayersMoney);
        }
        else{
            currentRoundBetsMap[currentPlayerName] = startingBet;
            bank.decreaseMoney(currentPlayerName, startingBet);
        }
    }
}

void System::processBet(const string& playerName, BetType betType ){
    int originalBet = currentRoundBetsMap.at(playerName);
    switch (static_cast<int> (betType)){
        case 0:                                                            //regular win
            bank.addMoney(playerName, 2*originalBet);
            return;
        case 1:
            bank.addMoney(playerName, 1.5*originalBet);         //naturalBlackJack win
            return;
        case 2:
            bank.addMoney(playerName, originalBet);                        //tie with the dealer
        default:
            cout << "BAD BAD BAD" <<endl;
            exit(0);
            return;
    }
}







/** dealer related functions */
void System::endOfRoundDealerBust(){
    cout << "The dealer has busted! All players who do not have a bust themselves win!" << endl;
    for (auto& player : this->PlayersVector){
        if(player->getCurrentHandSum() <= blackJackWinnerNum){ //player did not bust
            processBet(player->getName(), regular);
        }
    }
}

void System::endOfRoundPlayerBust(const string& playerName) {
    cout << playerName << " has a bust! He loses" << endl;
}

void System::printBankDetails() const {
    bank.printDetails();
}

void System::endRound() {
    printPlayerHands();
    printBankDetails();
    for (auto& player : PlayersVector){            //empty players card deck
        player->emptyDeck();
    }
    dealer.emptyDeck();                            //empty dealer card deck
}

void System::createPlayers(int numOfPlayers) {
    createRealPlayer();
    createAIPlayers(numOfPlayers);

}

void System::createRealPlayer() {
    cout << "Please select a name:" <<endl;
    string inputFromUser;
    getline(cin, inputFromUser);
    PlayersVector.push_back(unique_ptr<Player> (new RealPlayer(inputFromUser)));
    cout << endl;
}

void System::createAIPlayers(int numOfPlayers) {
    vector<string> vectorOfPossibleNames = {"Azula", "Zuko", "Uncle Iroh", "Ty Lee", "Scary Scar Guy", "Fire Lord Ozai",
                                            "Hama the Blood Bender", "Mai", "Appa", "Long Feng", "Jet", "Cabbage Man"};
    unsigned num = chrono::system_clock::now().time_since_epoch().count();    //generating a random number for shuffle function
    shuffle(vectorOfPossibleNames.begin(), vectorOfPossibleNames.end(), default_random_engine(num));
    for (int i=1 ; i < numOfPlayers; ++i){
        PlayersVector.push_back(unique_ptr<Player> (new AIPlayer(vectorOfPossibleNames[i])));
    }
}


