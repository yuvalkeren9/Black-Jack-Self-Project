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

    class terminateSystem;



    /**GUI related stuff */

    /**
     * Function that is responsible for creating the players and their stats GUI objects, background and texts
     */
    void setGameWindow();
    /**
     * Drawing the above objects to a window
     * @param window
     */
    void drawSetupWindow(sf::RenderWindow& window) const;

    /**
     * Helper function for setGameWindow. Creates AI GUI objects
     *
     * @param numOfAIPlayers how many AI players to create
     */

    /**
     * Helper function for setGameWindow. Creates AI GUI text objects
     * @param numOfAIPlayers how many AI player texts to create
     */
    void createAIPlayerTextObjects(int numOfAIPlayers);

    /**
     * Helper function for setGameWindow. Creates GUI stat objects
     */
    void createGameStatObjects();

    /**
     * Function that draws the GUI stats objects to the screen
     * @param window - which window to draw to
     */
    void drawStatsTextObjects(sf::RenderWindow& window) const;
    /**
     *
     * @param window
     */

    /**
     * Helper function that draws the location of each player. Helpful if a developer wants to add new features.
     * @param window the window to draw into
     */
    void drawPlayerLocations(sf::RenderWindow& window) const;

    /**
     * Animating the dealing of a card to a player
     * @param player the player to deal to
     * @param card the card to deal
     */
    void hitAPlayerGUI(Player* player, Card* card);

    /**
     * A helper function for the above function. This function does the actual animating, using specific coordinates.
     * @param startingPosition - where to start from
     * @param endingPosition - where to deliver card
     * @param cardSprite - sprite of the card to deal
     * @param window - which window to show the animation on
     */
    void animateCardDealt(const sf::Vector2<float> startingPosition, const sf::Vector2<float> endingPosition,
                          sf::Sprite& cardSprite, sf::RenderWindow& window) const;
    /**
     * Function that creates the button on the screen that allow the player to choose an action
     * @param positionToLocateButtons - position the locate the buttons on
     * @return
     */
    std::string realPlayerChooseActionGUI(sf::Vector2<float> positionToLocateButtons);

    /**
     * Function the shows an announcement on the screen
     * @param announcement - which string to show
     * @param delay - how long the announcement should stick on the screen
     */
    void announce(const std::string &announcement, float delay = 3);

    /**
     * Function responisble for rendering most of the basic GUI to a selected window
     * @param window - window to render to
     */
    void render(sf::RenderWindow& window) const;

    /**
     * Function that creates a texture for a card according to its type
     * @param card the card to create a texture for
     */
    void createCardTexture(Card*& card);

   /**
    * Function that loads files that the system will repeatedly use. To be used when setting up the game.
    */
    void loadFiles();

    /**
     * Function that animates flipping the dealer's second card
     */
    void flipDealerSecondCard();

    /**
     * Functions that are used for testing backend
     */
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


/**
 * Helper function for hitAPlayerGUI. Calculates where to deal a card to
 * @param startingPosition - where the card will start his movement from
 * @param cardSprite - the Sprite of the card
 * @param numberOfCardsInPlayerHand - how many cards already in player's hand
 * @param sizeOfCardDivisionOffset  - an offset to be used according to developers taste
 * @param isAI - is the player an AI
 * @return
 */
sf::Vector2<float> calculateWhereToDealCard(const sf::Vector2<float>& startingPosition, const sf::Sprite& cardSprite,
                                            int numberOfCardsInPlayerHand, float sizeOfCardDivisionOffset, bool isAI );




#endif //CARDGAME_SYSTEM_H
