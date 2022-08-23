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
#include "Cards/RegularNumCard.h"
#include <string>
#include <sstream>

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
//                tempVector.push_back(make_unique<Card> (j, intToCardTypeAdapter(p)));
                tempVector.push_back(unique_ptr<Card> (new RegularNumCard(j, intToCardTypeAdapter(p))));
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

System::System(std::queue<std::unique_ptr<Card>> deck, sf::RenderWindow* window, bool isWithGUI) : cardDeck(std::move(deck)), PlayersVector(), dealer("Dealer")
, isGameFinished(false), windowUsed(window), isWithGUI(isWithGUI) {
    int numOfPlayers = getNumberOfDesiredPlayers();
    createPlayers(numOfPlayers);
    addPlayersToBank();
    if (isWithGUI) {
        loadFiles();
        setGameWindow();
        createGameStatObjects();
    }
}

void System::dealStartingCards() {
    for (auto& player: this->PlayersVector){
        if (player->getIsAlive()) {
            for (int i = 0; i < amountOfStartingCards; ++i) {
                hitAPlayer(player.get());
                if(isWithGUI){
                    windowUsed->clear();
                    render(*windowUsed);
                    windowUsed->display();
                }
            }
        }
    }
    for (int i =0; i < amountOfStartingCards; ++i){
        Player* tempDealerPtr = &dealer;
        hitAPlayer(tempDealerPtr);
    }

}

void System::moveFirstCardToEndOfDeck() {
    unique_ptr<Card> temp = move(this->cardDeck.front());
    this->cardDeck.pop();
    this->cardDeck.push(move(temp));
}

bool System::playRound() {
    dealStartingCards();
    printPlayerHands();
    collectStartingBets();
    //checkIfPlayersWantToDoubleDown();
    printBankDetails();
    if(checkDealerForNaturalBlackJack()){
        endRound();
        if (isGameFinished) {
            return true;
        }
        else
            return false;
    }
    for (auto& player: this->PlayersVector){
        while(makeMove(player.get()));     //makeMove returns false when player decides to stand or is over 21
    }
    //TODO: dealer has a bust
    playDealerTurn();
    playResults();
    endRound();
    if (isGameFinished) {
        return true;
    }
    else
        return false;
}

bool System::checkPlayerForBlackJack(Player *player) {
    if(player->getCurrentHandSum() == blackJackWinnerNum){
        if(player->getAmountOfCardsInHand() == amountOfStartingCards) {
            processBet(player->getName(), naturalBlackjack);
            player->setIsAlive(false);
            cout << "Player " << *player << " has a BlackJack!" << endl;
            if(isWithGUI){
                string announcement = "Player " + player->getName() +" has a blackJack!";
                announce(announcement, 3);
            }

        }
        return true;
    }
    return false;
}

bool System::checkDealerForNaturalBlackJack() {
    if(dealer.getCurrentHandSum() == blackJackWinnerNum){
        cout << "The dealer has a Natural BlackJack!" << endl;
        if(isWithGUI){
            flipDealerSecondCard();
            announce("The dealer has a Natural BlackJack!", 3);
        }
        for (auto& player : PlayersVector){
            checkPlayerForBlackJack(player.get());
        }
        return true;
    }
    else {
        return false;
    }
}

void System::hitAPlayer(Player* player) {
    const auto& currentCard = this->cardDeck.front().get();
    player->hit(currentCard);   //giving the player a regular C pointer of a card
    moveFirstCardToEndOfDeck();
    if(isWithGUI){
         hitAPlayerGUI(player, currentCard);
    }
}

bool System::makeMove(Player* player){
    if(checkPlayerForBlackJack(player)){
        return false;
    }
    std::streambuf* orig = std::cin.rdbuf();
    if(isWithGUI){
        RealPlayer* realPlayerPtr = dynamic_cast<RealPlayer*>(player);       //second time breaking inhertiance (and final time)
        if (realPlayerPtr != nullptr) {             //is the current player a real player
            string actionAsString = realPlayerChooseActionGUI(sf::Vector2<float>(50,765));
            std::istringstream input(actionAsString);
            std::cin.rdbuf(input.rdbuf());
        }
    }
    Action action = player->chooseAction();
    std::cin.rdbuf(orig);
    bool canAnotherMoveBePlayed;
        switch(static_cast<int>(action)){
            case 0:
                cout<< "hitting player..." << *player << endl;
                hitAPlayer(player);
                if(player->getCurrentHandSum() > 21) {
                    cout << "Youre over 21, youre out!!" << endl;
                    canAnotherMoveBePlayed = false;
                    break;
                }
                else {
                    cout << "your current sum is:" << player->getCurrentHandSum() << endl;
                    canAnotherMoveBePlayed = true;
                    break;
                }
            case 1:
                cout<< "the following player decided to stand" << *player << endl;
                canAnotherMoveBePlayed = false;
                break;
            default:
                cout << "shit man something has gone way way wrong";
                exit(0);

        }
    return canAnotherMoveBePlayed;
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
        if(!player->getIsAlive()){
            continue;
        }
        const string currentPlayerName = player->getName();
        int currentPlayerSum = player->getCurrentHandSum();
        if(currentPlayerSum > blackJackWinnerNum) {
            endOfRoundPlayerBust(currentPlayerName);
            continue;
        }
        if (dealerSum == currentPlayerSum ){
            processBet(currentPlayerName, tie);
            cout << "Player " << *player << " is tied with the dealer!" << endl;
            if(isWithGUI){
                string announcement = "Player " + player->getName() + " is tied with the dealer!";
                announce(announcement, 1);
            }
        }
        else if (dealerSum > currentPlayerSum){
            cout << "Player " << *player << " has lost to the dealer!" << endl;
            if(isWithGUI){
                string announcement = "Player " + player->getName() + " has lost to the dealer!";
                announce(announcement, 1);
            }
//            continue;
        }
        else{                                     //player's sum is higher than dealer's
            processBet(currentPlayerName, regular);
            cout << "Player " << *player << " beat the dealer!" << endl;
            if(isWithGUI){
                string announcement = "Player " + player->getName() + " beat the dealer!";
                announce(announcement, 1);
            }
//            continue;
        }

        if(isWithGUI) {
            string playerName = player->getName();
            manager.getTextStatObject("currentSumTextPlayer" + playerName).setString(to_string(bank.getPlayersMoney(playerName)));
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
        if(!player->getIsAlive()){
            continue;
        }
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
        if(isWithGUI) {
            string playerName = player->getName();
            manager.getTextStatObject("currentSumTextPlayer" + playerName).setString(to_string(bank.getPlayersMoney(playerName)));
        }
    }
}

void System::checkIfPlayersWantToDoubleDown() {
    //TODO: this function, for real
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
            return;
        default:
            cout << "BAD BAD BAD" <<endl;
            exit(0);
    }
}







/** dealer related functions */
void System::endOfRoundDealerBust(){
    cout << "The dealer has busted! All players who do not have a bust themselves win!" << endl;
    announce("Dealer has busted! All player who did not bust win!");
    for (auto& player : this->PlayersVector){
        if(player->getCurrentHandSum() <= blackJackWinnerNum && player->getIsAlive()){ //player did not bust
            processBet(player->getName(), regular);
            announce("Player " + player->getName() + " has beat the dealer!");
        }
    }
}

void System::endOfRoundPlayerBust(const string& playerName) {
    cout << playerName << " has a bust! He (or she) loses" << endl;
    if(isWithGUI){
        string announcement = "Player " + playerName +" has a bust! He (or she) loses";
        announce(announcement, 3);
    }
}


void System::endRound() {
    printPlayerHands();
    printBankDetails();
    for (auto& player : PlayersVector){            //empty players card deck
        player->emptyDeck();
    }
    dealer.emptyDeck();    //empty dealer card deck
    if(isWithGUI){
        manager.emptyDeck();
    }
    checkAlivenessOfPLayers();
}


void System::createPlayers(int numOfPlayers) {
    createRealPlayer();
    createAIPlayers(numOfPlayers);
    //adding dealer to manager
    manager.addPlayer("Dealer", 250, 80);
    if(isGameFinished) {
        windowUsed->clear();
        render(*windowUsed);
        windowUsed->display();
    }
}

void System::createRealPlayer() {
    string inputFromUser;
    if(!isWithGUI) {
        cout << "Please select a name:" << endl;
    }
    getline(cin, inputFromUser);
    manager.addPlayer(inputFromUser, 250, 550);
    PlayersVector.push_back(unique_ptr<Player> (new RealPlayer(inputFromUser)));
}

void System::createAIPlayers(int numOfPlayers) {
    vector<string> vectorOfPossibleNames = {"Azula", "Zuko", "Uncle Iroh", "Ty Lee", "Scary Scar Guy", "Fire Lord Ozai",
                                            "Hama the Blood Bender", "Mai", "Appa", "Long Feng", "Jet", "Cabbage Man"};
    unsigned num = chrono::system_clock::now().time_since_epoch().count();    //generating a random number for shuffle function
    shuffle(vectorOfPossibleNames.begin(), vectorOfPossibleNames.end(), default_random_engine(num));
    for (int i=1 ; i < numOfPlayers; ++i){
        string playerName = vectorOfPossibleNames[i];
        if(PlayersVector[0]->getName() == playerName){ //checking that the Real player didn't use one of the names here.
            playerName = vectorOfPossibleNames.at(i+numOfPlayers); //If the player did pick a name, pick a different one outside the picking scope
        }
        sf::Vector2<float> playerLocation = calculateWhereToLocatePlayer(i);
        manager.addPlayer(playerName, playerLocation);
        PlayersVector.push_back(unique_ptr<Player> (new AIPlayer(playerName)));
    }
}









/**Testing realted functions */

int System::getPlayersCurrentMoney(int numberOfPlayer) const {
    assert(numberOfPlayer > 0);
    return bank.getPlayersMoney(PlayersVector[numberOfPlayer - 1]->getName()); //One liner! :)
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

void System::printBankDetails() const {
    bank.printDetails();
}

void System::checkAlivenessOfPLayers() {
    auto it = PlayersVector.begin();
    while ( it != PlayersVector.end()){
        const string currentPlayerName = (*it)->getName();
        if(bank.getPlayersMoney(currentPlayerName) == 0){
            removePlayer(it->get());
        }
        else{
            (*it)->setIsAlive(true);
            ++it;
        }
    }
    auto playersStillInGame = PlayersVector.size();
    if (playersStillInGame == 1){
        cout << "We have a winner!! Player " << PlayersVector[0]->getName() <<" is the BlackJack Master!" << endl;
        isGameFinished = true;
        return;
    }
    if (playersStillInGame == 0){
        cout << "We have a tie! What are the odds??" << endl;
        isGameFinished = true;
        return;
    }
}

void System::removePlayer(Player *player) {
    for(auto it = PlayersVector.begin(); it != PlayersVector.end(); ++it){
        const string currentPlayerName= (*it)->getName();
        if (currentPlayerName == player->getName()){
            //TODO: forshadow with gui
            bank.removePlayerFromBank(currentPlayerName);
            PlayersVector.erase(it);
            return;
        }
    }
}





