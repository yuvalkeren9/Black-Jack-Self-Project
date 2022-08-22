//
// Created by יובל קרן on 8/5/2022.
//

#ifndef CARDGAME_CARD_H
#define CARDGAME_CARD_H

#include <queue>
#include <cstdlib>
#include <memory>
#include <SFML/Graphics.hpp>


enum CardShape {Clubs, Diamonds, Hearts, Spades};

class Card {
private:
    CardShape type;

protected:
    int value;
    sf::Texture cardTexture;
public:
    virtual void print(std::ostream& os) const;
    Card(int value, CardShape type) : value(value), type(type) {};
    virtual ~Card() = default;
    class intToCardTypeError;
    int getValue() const;
    std::string getCardShapeAsString();




    /** GUI related stuff */
    const sf::Texture & getTexture() const;   //maybe refrence is a problem

};


CardShape intToCardTypeAdapter(int value);
std::string createStringForCardTypeSprite(Card& card);





#endif //CARDGAME_CARD_H
