//
// Created by יובל קרן on 8/8/2022.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H
#include <utility>

#include "../Cards/card.h"

/**
 * Enum for different action types
 */
enum Action {Hit, Stand};

/**
 * The player class. This is a base class for an AI player and a real player.
 */
class Player {
private:
    std::vector<Card*> m_playerHand;
    std::string m_name;
    bool isAlive;
    const static int sizeOfHigherValueAce = 11;


public:
    explicit Player(std::string name) : m_playerHand(), m_name(std::move(name)), isAlive(true) {};
    virtual ~Player() = default;

    /**
     * Function that adds a card to the player's deck
     * @param newCard the card to add
     */
    void addToDeck(Card* newCard);

    /**
     * Removes all the players cards
     */
    void emptyDeck();
    /**
     * Calculates the current sum of the players cards
     * @return The sum of the cards
     */
    int getCurrentHandSum() const;
    /**
     * Print function
     */
    void print() const;

    /**
     * Function that prints the players hand. Usefull for debugging.
     */
    void printHand() const;

    /**
     * setter of the isAlive field
     * @param boolCondition param to set isAlive field
     */
    void setIsAlive(bool boolCondition);

    /**
     * getter for the isAlive field
     * @return isAlive param
     */
    bool getIsAlive() const;

    /**
     *
     * @return amount of cards in hand of a player
     */
    int getAmountOfCardsInHand() const;

    /**
     * Changes an ace value from 11 to 1, if needed.
     */
    void updateAces();

    /**
     *
     * @return Player's name
     */
    std::string getName() const;

    /**
     * virtual function that returns what action to do
     * @return what action to do
     */
    virtual Action chooseAction() const = 0;


    /** Game Moves */

    /**
     * hitting a player with a card
     * @param newCard the card to hit with
     */
    void hit(Card* newCard);

    /**
     * helper function to change an Ace from one to eleven.
     */
    void changeAceFromOneToEleven();

    /**
     * helper function to change an Ace from eleven to one.
     */
    void changeAceFromElevenToOne();
};

/**
 * prints the player's name to an output stream.
 * @param os output stream to print to
 * @param player player to print
 * @return output stream reference to allow chaining
 */
std::ostream& operator<<(std::ostream& os, const Player& player);

#endif //MAIN_CPP_PLAYER_H
