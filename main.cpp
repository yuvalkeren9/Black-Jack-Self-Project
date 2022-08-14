#include <iostream>
#include "Cards/card.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "Cards/AceCard.h"
#include "Cards/RoyaltyCard.h"


int main() {
    //creating a deck
//    std::queue<std::unique_ptr<Card>> forTesting;
//    forTesting.push(std::unique_ptr<Card> (new AceCard(intToCardTypeAdapter(1))));
//    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(2), Jack)) );
//    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(2), Jack)) );
//    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(2), Jack)) );
//    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(2), Jack)) );
//    forTesting.push(std::unique_ptr<Card> (new AceCard(intToCardTypeAdapter(2))));
//    System s(move(forTesting), 2);







    System s(createRegularCardDeck(1), 2);
    for(int i=1; i< 5; ++i) {
        std::cout << "Round " << i <<" !" << std::endl << std::endl;
        s.playRound();
    }



//    s.printCards();
//    sf::RenderWindow window(sf::VideoMode(640, 480), "BlackJack game");
//    sf::CircleShape shape;
//    shape.setRadius(40.f);
//    shape.setPosition(100.f, 100.f);
//    shape.setFillColor(sf::Color::Cyan);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
    return 0;
}
