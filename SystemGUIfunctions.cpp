//
// Created by יובל קרן on 8/17/2022.
//

#include "System.h"
using namespace std;

void System::setGameWindow(sf::RenderWindow& window) {
    //TODO: make a font thing so that you dont have to load it over and over again
    manager.setBackground("C:/Program Files/clionprojects/cardgame/GUIfiles/Sprites/pokerGameBackground.jpg");

    const sf::Font& marlboroFont = manager.getFont("marlboroFont");
    const sf::Font& westernFont = manager.getFont("westernFont");

    /**drawing dealer */
    sf::Text dealerNameText("Dealer", westernFont, 60);
    auto dealerSize = dealerNameText.getLocalBounds();
    dealerNameText.setOrigin((dealerSize.width)/2, (dealerSize.height)/2);
    dealerNameText.setPosition(600,20);
    manager.addTextObject("dealerNameText", dealerNameText,1);

    /** drawing Real player*/
    sf::Text playerNameText(PlayersVector[0]->getName(), westernFont, 60);
    auto playerNameTextSize = playerNameText.getLocalBounds();
    playerNameText.setOrigin((playerNameTextSize.width)/2, (playerNameTextSize.height)/2);
    playerNameText.setPosition(600,750);
    manager.addTextObject("playerNameText", playerNameText,1);

    /**Real player amount of money text */
    sf::Text playerCurrentSumOfHandHeaderText("Current sum of your hand is:", marlboroFont, 30);
    auto playerCurrentSumOfHandHeaderTextSize = playerCurrentSumOfHandHeaderText.getLocalBounds();
    playerCurrentSumOfHandHeaderText.setOrigin(playerCurrentSumOfHandHeaderTextSize.width,0);
    playerCurrentSumOfHandHeaderText.setPosition(600,800);
    manager.addTextObject("playerCurrentSumOfHandHeaderText", playerCurrentSumOfHandHeaderText,1);

    /**Real player current money*/
    sf::Text playerCurrentMoneyHeaderText("Current amount of money:", marlboroFont, 30);
    auto locationOfAboveText = playerCurrentSumOfHandHeaderText.getGlobalBounds();
    playerCurrentMoneyHeaderText.setPosition(600 - locationOfAboveText.width,835);
    manager.addTextObject("playerCurrentMoneyHeaderText", playerCurrentMoneyHeaderText,1);

    for (int i = 1; i < PlayersVector.size(); ++i){
        createAIPlayerTextObjects(i);
    }
}

void System::createAIPlayerTextObjects(int playerNumber) {

    const sf::Font& marlboroFont = manager.getFont("marlboroFont");
    sf::Text playerNameText(PlayersVector[playerNumber]->getName(), marlboroFont, 30);
    sf::Text playerCurrentMoneyText("Money:", marlboroFont, 20);

    switch(playerNumber){
        case 1:
            playerNameText.setPosition(0,200);
            playerCurrentMoneyText.setPosition(0,200 + bankTextOffset);
            manager.addTextObject("player2NameText", playerNameText, 1);
            manager.addTextObject("player2CurrentMoneyText", playerCurrentMoneyText, 1);
            break;
        case 2:
            playerNameText.setPosition(900,200);
            playerCurrentMoneyText.setPosition(900,200 + bankTextOffset);
            manager.addTextObject("player3NameText", playerNameText, 1);
            manager.addTextObject("player3CurrentMoneyText", playerCurrentMoneyText, 1);
            break;
        case 3:
            playerNameText.setPosition(900,500);
            playerCurrentMoneyText.setPosition(900,500 + bankTextOffset);
            manager.addTextObject("player4NameText", playerNameText, 1);
            manager.addTextObject("player4CurrentMoneyText", playerCurrentMoneyText, 1);
            break;
        case 4:
            playerNameText.setPosition(0,500);
            playerCurrentMoneyText.setPosition(0,500 + bankTextOffset);
            manager.addTextObject("player5NameText", playerNameText, 1);
            manager.addTextObject("player5CurrentMoneyText", playerCurrentMoneyText, 1);
            break;
        default:
            cout << "TRIED TO DRAW A PLAYER THAT DOES NOT EXIST" << endl;
            return;
    }
}


void System::drawSetupWindow(sf::RenderWindow& window) const {
    manager.drawBackground(window);
    manager.drawSetupTextObjects(window);
}

//TODO: can simplify this. Do this when project is done and needs to look more neat.
void System::createGameStatObjects() {
    //TODO: for every player, draw money, and for REAL player draw hand
    const int realPlayerTextOffset = 50;
    const int AIplayersTextOffset = 20;
    const sf::Font &marlboroFont = manager.getFont("marlboroFont");
    sf::Text currentSumText(to_string(PlayersVector[0]->getCurrentHandSum()), marlboroFont, 30);
    auto &playerNameTextHeader = manager.getTextObject("playerCurrentSumOfHandHeaderText");

//TODO: make this normal
    auto playerNameTextHeaderGlobalPosition = playerNameTextHeader.getGlobalBounds();
    auto playerNameTextHeaderLocalPosition = playerNameTextHeader.getLocalBounds();
    currentSumText.setPosition(playerNameTextHeaderGlobalPosition.left + playerNameTextHeaderGlobalPosition.width + realPlayerTextOffset,
                               playerNameTextHeaderGlobalPosition.top - playerNameTextHeaderLocalPosition.top);
    manager.addTextObject("currentSumTextRealPlayer",currentSumText, 2);

    for (int i = 0; i < PlayersVector.size(); ++i) {
        const string playerMoneyString = to_string(bank.getPlayersMoney(PlayersVector[i]->getName()));
        sf::Text playerMoneyText (playerMoneyString, marlboroFont, 20);
        switch (i) {
            case 0: {
                playerMoneyText.setCharacterSize(30);
                auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextObject("playerCurrentMoneyHeaderText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + realPlayerTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject("currentSumTextPlayer1",playerMoneyText, 2);

                break;
            }
            case 1:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextObject("player2CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset ,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject("currentSumTextPlayer2",playerMoneyText, 2);
                break;
            }

            case 2:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextObject("player3CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject("currentSumTextPlayer3",playerMoneyText, 2);
                break;
            }
            case 3:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextObject("player4CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject("currentSumTextPlayer4",playerMoneyText, 2);
                break;
            }
            case 4:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextObject("player5CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject("currentSumTextPlayer5",playerMoneyText, 2);
                break;
            }
                default:
                cout << "Trying to draw character stat that doesnt exist" << endl;
                break;
        }
    }
}

void System::drawStatsTextObjects(sf::RenderWindow &window) const {
    manager.drawStatTextObjects(window);
}

int System::getNumberOfPlayers() const {
    string temp;
    if(!isWithGUI){
        cout << "Enter number of players (1-5)" << endl;
    }
    //TODO: check for valid input
    getline(cin, temp);
    return stoi(temp);
}


void System::render(sf::RenderWindow &window) const {
    window.clear();
    drawSetupWindow(window);
    drawStatsTextObjects(window);
    manager.drawPlayerLocations(window);
    window.display();
}

sf::Vector2<float> calculateWhereToLocatePlayer(int i){
    const float offset = 75;
    float x;
    float y;
    switch (i){
        case 1:
            x = 0;
            y = 200 + offset;
            break;
        case 2:
            x = 900;
            y = 200 + offset;
            break;
        case 3:
            x = 900;
            y = 500 + offset;
            break;
        case 4:
            x = 0;
            y = 500 + offset;
            break;
        default:
            cout << "too many players...";
            throw logic_error("You tried to set too many player locations");
    }
    return {x,y};
}


void System::drawPlayerLocations(sf::RenderWindow& window) const {
    manager.drawPlayerLocations(window);
}
