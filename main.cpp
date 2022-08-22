#include <iostream>
#include "Cards/card.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "Cards/AceCard.h"
#include "Cards/RoyaltyCard.h"
#include "Cards/RegularNumCard.h"
#include "GUImanager/Textbox.h"

using namespace std;

/** Functions to help set up GUI system*/
string getPlayerSettingAsString(sf::RenderWindow& window);



int main() {
    /** Creating game window */
    sf::RenderWindow window(sf::VideoMode(1200, 880), "BlackJack game");
    sf::RenderWindow* windowPtr = &window;


    /** setting up system */

    std::streambuf* orig = std::cin.rdbuf();
    string stringToInjectIntoCin = getPlayerSettingAsString(window);
    std::istringstream input(stringToInjectIntoCin);
    std::cin.rdbuf(input.rdbuf());
    System s(createRegularCardDeck(1),windowPtr, true);
    std::cin.rdbuf(orig);

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        s.playRound();
        window.clear();
        s.drawSetupWindow(window);
        s.drawStatsTextObjects(window);
        s.drawPlayerLocations(window);
        window.display();
    }
    return 0;
}
//
//int main(){
//        System s(createRegularCardDeck(1),nullptr);
//        while(s.playRound());
//};




string getPlayerSettingAsString(sf::RenderWindow& window){
    /** loading background*/
    sf::Texture dogsBackground;
    dogsBackground.loadFromFile("C:/Program Files/clionprojects/cardgame/GUIfiles/Sprites/dogsBackground.jpg");
    sf::Sprite dogsBackgroundSprite;
    dogsBackgroundSprite.setTexture(dogsBackground);
    dogsBackgroundSprite.setScale(1.5,1.5);


    /**loading font*/
    sf::Font marlboro;
    marlboro.loadFromFile("C:/Program Files/clionprojects/cardgame/GUIfiles/Fonts/Marlboro.ttf");
    
    /** creating regular text objects*/
    sf::Text welcomeMessage("Welcome to Yuval's BlackJack!", marlboro, 60);
    auto welcomeMessageSize = welcomeMessage.getLocalBounds();
    welcomeMessage.setOrigin((welcomeMessageSize.width)/2, (welcomeMessageSize.height)/2);
    welcomeMessage.setPosition(600,100);

    sf::Text enterNumOfPlayersText("Please enter number of player (1-5)",marlboro,30);
    enterNumOfPlayersText.setPosition(300,200);

    sf::Text enterPlayerNameText("Please enter the name you wish to play with", marlboro, 30);
    enterPlayerNameText.setPosition(300,200);

    sf::Text createdBy("This game was created by Yuval Keren, feel free to copy whatever! Have fun :)", marlboro, 40);
    createdBy.setPosition(0,800);
    
    
    /** creating text boxes */
    Textbox textboxForNumOfPlayers;
    textboxForNumOfPlayers.setPosition(900, 200);
   
    textboxForNumOfPlayers.setFont(marlboro);

    Textbox textboxForName;
    textboxForName.setPosition(900, 200);
    textboxForName.setFont(marlboro);


    bool didUserFinish = false;
    int whichStepToDo = 1;                 //in order to receive users input in a certain order,
    // we track which input the user is entering now (num of players, user name, etc..)

    string stringToInjectIntoCin;
    while(window.isOpen() && !didUserFinish){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered && whichStepToDo == 1){
                if(event.text.unicode == 13){
                    whichStepToDo = 2;
                    stringToInjectIntoCin += textboxForNumOfPlayers.getString() + "\n";  //so when doing future +=, there will be a \n between words
                    continue;
                }
                textboxForNumOfPlayers.typedOn(event);
            }
            if (event.type == sf::Event::TextEntered && whichStepToDo == 2){
                if(event.text.unicode == 13){
                    didUserFinish = true;
                    stringToInjectIntoCin += textboxForName.getString();
                    continue;
                }
                textboxForName.typedOn(event);
            }
            //TODO: only when a valid string was entered
        }

        /** drawing */
        window.clear();
        window.draw(dogsBackgroundSprite);
        window.draw(welcomeMessage);
        window.draw(createdBy);
        switch (whichStepToDo){
            case 1:
                window.draw(enterNumOfPlayersText);
                textboxForNumOfPlayers.drawTo(window);
                break;
            case 2:
                window.draw(enterPlayerNameText);
                textboxForName.drawTo(window);
                break;
            default:
                cout << "Bug in setUp window";
                break;
        }
        window.display();
    }
    return stringToInjectIntoCin;
}
