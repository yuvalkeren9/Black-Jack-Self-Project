//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_CARD_H
#define CARDGAME_CARD_H

#include <queue>
#include <cstdlib>
#include <memory>
#include <SFML/Graphics.hpp>

/**
 * Enum for different card shapes
 */
enum CardShape {Clubs, Diamonds, Hearts, Spades};

/**
 * The Card class. This is a base class for a regular card, an Ace card, and a Royalty card
 */
class Card {
private:
    CardShape type;

protected:
    int value;

public:

    Card(int value, CardShape type) : value(value), type(type) {};
    virtual ~Card() = default;

    /**
     * Function that prints the card type and value
     * @param os out stream to print to
     */
    virtual void print(std::ostream& os) const;

    /**
     * Class for throwing exception
     */
    class intToCardTypeError;

    /**
     * getter of the value of a card
     * @return value of card
     */
    int getValue() const;

    /**
     * getter that returns the card shape as a string
     */
    std::string getCardShapeAsString() const;

    /**
     * full name of card as a string. Usefull for GUI (loading files)
     */
    virtual std::string getCardFullNameAsString() const = 0;

};

/**
 * an adapter that changes an int to an enum CardType. 1 for clubs, 2 for diamonds, 3 for hearts, 4 for spades.
 * @param value an integer between 1-4. Will throw exception if a diffrent number is used
 * @return enum of CardType
 */
CardShape intToCardTypeAdapter(int value);

#endif //CARDGAME_CARD_H
