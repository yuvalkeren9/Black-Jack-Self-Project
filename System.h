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
#include "GUImanager/GUImanager.h"


class System {
private:
    /** class members */
    std::queue<std::unique_ptr<Card>> cardDeck;
    std::vector<std::unique_ptr<Player>> PlayersVector;
    AIPlayer dealer;
    Bank bank;
    std::unordered_map<std::string, int> currentRoundBetsMap;
    bool isGameFinished;

    GUImanager manager;
    sf::RenderWindow* windowUsed;
    bool isWithGUI;

   /**backend consts */
    const static int blackJackWinnerNum = 21;
    const static int startingBet = 100;
    const static int amountOfStartingCards = 2;

    /** GUI consts*/
    static const int bankTextOffset = 35;

    enum BetType  {regular, naturalBlackjack, tie};

    //functions that are used when setting up the system, and the start of a round

    /**
     * moves the top card in the deck to the bottom
     */
    void moveFirstCardToEndOfDeck();

    /**
     * Deals amountOfStartingCards to every player, including dealer. The class constant is defualty set to 2,
     * as blackjack rules suggest.
     */
    void dealStartingCards();

    /**
     * Adds a player to the bank that the system object has
     */
    void addPlayersToBank();

    /**
     * function that collects a bet from every player at the beginning of every round. Takes the amount that is set in the class constant
     * "startingBet". If a player has less than startingBet, the bet that is taken is all of the remaining money.
     */
    void collectStartingBets();

    /**
     * Creating players for the system to hold.
     * @param numOfPlayers how many players to create
     */
    void createPlayers(int numOfPlayers);
    /**
     * A helper function for the createPlayers function. Creates the real player.
     */
    void createRealPlayer();

    /**
     * A helper function for the createPlayers function. Creates the AI players.
     * @param numOfPlayers - how many AI players to create
     */
    void createAIPlayers(int numOfPlayers);

    /**
     * A helper function at the beggining of the game to collect input from user about how many players should play.
     * Does both GUI and regular games.
     * @return number of desired players
     */
    int getNumberOfDesiredPlayers() const;

    //functions that check for blackJack, and also process the bet if the player did have a blackjack.

    bool checkPlayerForBlackJack(Player *player);
    bool checkDealerForNaturalBlackJack ();

    //Member functions for mid-round.
    /**
     * Deal a card to a player. Function also handles moving the card to the end of the deck.
     * @param player - the player to hit
     */
    void hitAPlayer(Player* player);

    /**
     * Function that handles a player's move. Returns whether another move can be made.
     * @param player - the player whose turn it is to make a move
     * @return Returns whether another move can be made (if a player has a bust function returns false,
     * if player can hit again returns true, etc)
     */
    bool makeMove(Player* player);

    /**
     * Handling the dealers turn. According to blackjack rules, dealer has to hit until he has 17 or more.
     */
    void playDealerTurn();




    //Functions for ending a round

    /**
     * The main function that process the end of a round, and starts to prepare the next round.
     * Basically calls many other smaller functions
     */
    void endRound();

    /**
     * The name is a little misleading, but I kept it because it was funny to me, and this is my project so I can do siily stuff
     * from time to time. Function that checks whether there is a winner, and acts accordingly
     */
    void checkAlivenessOfPLayers();

    /**
     * If a player has no more money, removes it from the game
     * @param player - player to remove
     */
    void removePlayer(Player* player);

    /**
     * Runs player by player and checks their card score against the dealer, and handles bets accordingly.
     */
    void playResults();

    /**
     * Helper function for the playResults function. Handles situations when the dealer has a bust.
     */
    void endOfRoundDealerBust();
    /**
     * Helper function for the playResults function. Handles situations when the player given has a bust.
     * @param playerName - a player who has a bust
     */
    void endOfRoundPlayerBust(const std::string& playerName);




    void checkIfPlayersWantToDoubleDown();

    /**
     * Function that process a bet. Function communicates with the system bank.
     * @param playerName - the player to process has bank
     * @param betType - which type of bet to process (loss, tie, natural blackJack etc...)
     */
    void processBet(const std::string& playerName, BetType betType);



public:
    /**
     * The constructor of System object. Can construct both boolean and cmd games. If you want to simulate a graphical game,
     * then you first need to download the sfml library, and then pass the function a pointer to an open window.
     *
     * @param deck - a deck of cards to play with (can be any deck!)
     * @param window - a pointer to a SFML window
     * @param isWithGUI a boolean value to signal the system whether the use wants a graphical interface or a CMD interface.
     */
    System(std::queue<std::unique_ptr<Card>> deck, sf::RenderWindow* window, bool isWithGUI = false);

    /**
     * A main function of the System object. Simulates a single round of blackjack. This function handles everything from dealing
     * cards at the start, up to collecting bets as the round is finished
     * @return whether another round can be played or not (if all player but one lost all their money / tie)
     */
    bool playRound();



    /**GUI related stuff */
    void setGameWindow();
    void drawSetupWindow(sf::RenderWindow& window) const;
    void createAIPlayerTextObjects(int numOfAIPlayers);
    void createGameStatObjects();
    void drawStatsTextObjects(sf::RenderWindow& window) const;
    void drawPlayerLocations(sf::RenderWindow& window) const;
    void hitAPlayerGUI(Player* player, Card* card);
    void animateCardDealt(const sf::Vector2<float> startingPosition, const sf::Vector2<float> endingPosition,
                          sf::Sprite& cardSprite, sf::RenderWindow& window);
    std::string realPlayerChooseActionGUI(sf::Vector2<float> positionToLocateButtons);
    void announce(const std::string &announcement, float delay = 3);
    void render(sf::RenderWindow& window) const;


   /**
    * Function that loads files that the system will repeatedly use. To be used when setting up the game.
    */
    void loadFiles();



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

/**
 * Function that calculates where to locate AI players on the window
 * @param AI player to locate
 * @return Vector of the location
 */
sf::Vector2<float> calculateWhereToLocatePlayer(int i);

sf::Vector2<float> calculateWhereToDealCardAIPlayer(const sf::Vector2<float>& startingPosition, const sf::Sprite& cardSprite,
                                                    int numberOfCardsInPlayerHand, float sizeOfCardDivisionOffset, bool isAI );


#endif //CARDGAME_SYSTEM_H
