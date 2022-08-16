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
#include "Players/AIPlayer.h"
#include "Bank/Bank.h"


class System {
private:
    /** class members */
    std::queue<std::unique_ptr<Card>> cardDeck;
    std::vector<std::unique_ptr<Player>> PlayersVector;
    AIPlayer dealer;
    Bank bank;
    std::unordered_map<std::string, int> currentRoundBetsMap;
    bool isGameFinished;

    const static int blackJackWinnerNum = 21;
    const static int startingBet = 100;
    const static int amountOfStartingCards = 2;
    enum BetType  {regular, naturalBlackjack, tie};

    /**class member functions */
    void moveFirstCardToEndOfDeck();
    void dealStartingCards();

    bool checkPlayerForBlackJack(Player *player);
    bool checkDealerForNaturalBlackJack ();


    void hitAPlayer(Player* player);
    bool makeMove(Player* player);
    void playDealerTurn();


    void createPlayers(int numOfPlayers);
    void createRealPlayer();
    void createAIPlayers(int numOfPlayers);


    void playResults();
    void endOfRoundDealerBust();
    void endOfRoundPlayerBust(const std::string& playerName);


    void endRound();
    void checkAlivenessOfPLayers();
    void removePlayer(Player* player);


    void addPlayersToBank();
    void collectStartingBets();
    void checkIfPlayersWantToDoubleDown();
    void processBet(const std::string& playerName, BetType betType);





        public:

    /** Constructor for the System class. Doesn't create its own deck so that any sort of and amount of cards can be played. */
    explicit System(std::queue<std::unique_ptr<Card>> deck, int numOfPlayers);



//Is a private function, only here for testing (make it private when you finish)
    bool playRound();

    //for testing
    void printPlayerHands() const;
    void printBankDetails() const;
    int getPlayersCurrentMoney(int numberOfPlayer) const;

};



/**
 * Function that generates a regular card deck.
 * @param numOfDecks - how many "regular" decks to be created in the deck (some casinos play BlackJack with 3 decks)
 * @return shuffled card deck
 */
std::queue<std::unique_ptr<Card>> createRegularCardDeck(int numOfDecks);


#endif //CARDGAME_SYSTEM_H
