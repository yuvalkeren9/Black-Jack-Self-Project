#include <iostream>
#include "Cards/card.h"
#include "System.h"
#include <SFML/Graphics.hpp>


int main() {
    System s(createRegularCardDeck(1), 2);
    s.printPlayerHands();
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
