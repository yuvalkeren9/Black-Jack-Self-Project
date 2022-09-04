#include <iostream>
#include "Cards/card.h"
#include "System.h"
#include "GUImanager/Textbox.h"

using namespace std;

/** Function to help set up GUI system*/
string getPlayerSettingAsString(sf::RenderWindow& window);

static const int ENTER_KEYBOARD_BUTTON = 13;
static const int ONE_KEYBOARD_BUTTON = 49;
static const int FIVE_KEYBOARD_BUTTON = 53;
static const int BACKSPACE_KEY = 8;



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
        try {
            s.playRound();
        }
        catch(exception& error){
            window.close();
            return 0;
        }
        window.clear();
        s.drawSetupWindow(window);
        s.drawStatsTextObjects(window);
        window.display();
    }
    return 0;
}




/** Function that is responsible for the setup menu*/
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

    sf::Text badInput("Only numbers between 1-5 my good friend!", marlboro, 50);
    badInput.setPosition(300, 300);
    
    /** creating text boxes */
    Textbox textboxForNumOfPlayers(marlboro, true, 1);
    textboxForNumOfPlayers.setPosition(900, 200);

    Textbox textboxForName(marlboro, true, 20);
    textboxForName.setPosition(850, 200);


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
                auto keyPressed =event.text.unicode;
                if(keyPressed == ENTER_KEYBOARD_BUTTON){
                    whichStepToDo = 2;
                    stringToInjectIntoCin += textboxForNumOfPlayers.getString() + "\n";  //so when doing future +=, there will be a \n between words
                    continue;
                }
                else if  ((keyPressed >= ONE_KEYBOARD_BUTTON && keyPressed <= FIVE_KEYBOARD_BUTTON) || keyPressed == BACKSPACE_KEY  ){
                    textboxForNumOfPlayers.typedOn(event);
                }
                else{
                    window.clear();
                    window.draw(dogsBackgroundSprite);
                    window.draw(welcomeMessage);
                    window.draw(createdBy);
                    window.draw(badInput);
                    window.display();
                    sf::sleep(sf::seconds(1.5));

                }
            }
            if (event.type == sf::Event::TextEntered && whichStepToDo == 2){
                if(event.text.unicode == 13){
                    didUserFinish = true;
                    stringToInjectIntoCin += textboxForName.getString();
                    continue;
                }
                textboxForName.typedOn(event);
            }
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
                cout << "Bug in setup window";
                break;
        }
        window.display();
    }
    return stringToInjectIntoCin;
}
