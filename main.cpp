#include <iostream>
#include "Cards/card.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "Cards/AceCard.h"
#include "Cards/RoyaltyCard.h"
#include "Cards/RegularNumCard.h"

using namespace std;


int main() {
    System s(createRegularCardDeck(1), 3);
//    for(int i=1; i< 5; ++i) {
//        std::cout << "Round " << i <<" !" << std::endl << std::endl;
//        s.playRound();
//    }
      RegularNumCard card1(5, Hearts);
      RoyaltyCard card2(Diamonds, Jack);
      AceCard card3(Spades);

      /** Creating game window */
      sf::RenderWindow window(sf::VideoMode(1200, 880), "BlackJack game");

      /** settting up starting window*/


      sf::Texture texture;
      texture.loadFromImage(card2.getImage());  //Load Texture from image
      sf::Sprite sprite;
      sprite.setTexture(texture);
      sprite.setPosition(200, 350);
      sprite.setScale(0.5,0.5);


      while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        s.setGameWindow(window);
        window.draw(sprite);
        window.display();
      }
      return 0;
}
