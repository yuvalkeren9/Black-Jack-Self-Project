//
// Created by יובל קרן on 8/17/2022.
//

#include "System.h"
#include "Players/RealPlayer.h"
#include "GUImanager/Textbox.h"
#include <exception>

using namespace std;

class System::terminateSystem : public exception{
public:
    terminateSystem() = default;
    const char *what() const noexcept override {
        return "Exiting program, cleanly";
    }
};

void System::setGameWindow() {
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


void System::createGameStatObjects() {
    const int realPlayerTextOffset = 50;
    const int AIplayersTextOffset = 20;
    const sf::Font &marlboroFont = manager.getFont("marlboroFont");
    sf::Text currentSumText(to_string(PlayersVector[0]->getCurrentHandSum()), marlboroFont, 30);
    auto &playerNameTextHeader = manager.getTextSetupObject("playerCurrentSumOfHandHeaderText");

    auto playerNameTextHeaderGlobalPosition = playerNameTextHeader.getGlobalBounds();
    auto playerNameTextHeaderLocalPosition = playerNameTextHeader.getLocalBounds();
    currentSumText.setPosition(playerNameTextHeaderGlobalPosition.left + playerNameTextHeaderGlobalPosition.width + realPlayerTextOffset,
                               playerNameTextHeaderGlobalPosition.top - playerNameTextHeaderLocalPosition.top);
    manager.addTextObject("currentSumTextRealPlayer",currentSumText, 2);

    for (int i = 0; i < PlayersVector.size(); ++i) {
        const string playerMoneyString = to_string(bank.getPlayersMoney(PlayersVector[i]->getName()));
        sf::Text playerMoneyText (playerMoneyString, marlboroFont, 20);
        string nameOfObject = "currentSumTextPlayer" + PlayersVector[i]->getName();
        switch (i) {
            case 0: {
                playerMoneyText.setCharacterSize(30);
                auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextSetupObject("playerCurrentMoneyHeaderText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + realPlayerTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject(nameOfObject,playerMoneyText, 2);

                break;
            }
            case 1:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextSetupObject("player2CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset ,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject(nameOfObject,playerMoneyText, 2);
                break;
            }

            case 2:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextSetupObject("player3CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject(nameOfObject,playerMoneyText, 2);
                break;
            }
            case 3:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextSetupObject("player4CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject(nameOfObject ,playerMoneyText, 2);
                break;
            }
            case 4:{auto &playerCurrentMoneyHeaderTextRefrence = manager.getTextSetupObject("player5CurrentMoneyText");
                auto currentEditedTextGlobalBounds = playerCurrentMoneyHeaderTextRefrence.getGlobalBounds();
                auto currentEditedTextLocalBounds = playerCurrentMoneyHeaderTextRefrence.getLocalBounds();
                playerMoneyText.setPosition(currentEditedTextGlobalBounds.left + currentEditedTextGlobalBounds.width + AIplayersTextOffset,
                                            currentEditedTextGlobalBounds.top - currentEditedTextLocalBounds.top);
                manager.addTextObject(nameOfObject, playerMoneyText, 2);
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

int System::getNumberOfDesiredPlayers() const {
    string temp;
    if(!isWithGUI){
        cout << "Enter number of players (1-5)" << endl;
    }
    getline(cin, temp);
    return stoi(temp);
}


void System::render(sf::RenderWindow &window) const {
    drawSetupWindow(window);
    drawStatsTextObjects(window);
    manager.drawCardSprites(window);
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


void System::loadFiles(){
    manager.addFont("marlboroFont", "C:/Program Files/clionprojects/cardgame/GUIfiles/Fonts/Marlboro.ttf");
    manager.addFont("westernFont", "C:/Program Files/clionprojects/cardgame/GUIfiles/Fonts/Old Town Regular.ttf");
}



void System::animateCardDealt(const sf::Vector2<float> startingPosition, const sf::Vector2<float> endingPosition, sf::Sprite& cardSprite, sf::RenderWindow& window) const {
    cardSprite.setPosition(startingPosition);
    float xDistance = endingPosition.x - startingPosition.x;
    float yDistance = endingPosition.y - startingPosition.y;
    float xVelocity = (xDistance / 500);
    float yVelocity = (yDistance / 500);
    sf::Event closedEvent;
    for (int i =0; i < 500; ++i) {
        while (window.pollEvent(closedEvent)) {
            if (closedEvent.type == sf::Event::Closed) {
                throw System::terminateSystem();
            }
        }
            cardSprite.move(xVelocity, yVelocity);
            window.clear();
            render(window);
            window.draw(cardSprite);
            window.display();
        }
}




void System::hitAPlayerGUI(Player *player, Card* card) {
    int numberOfCards = player->getAmountOfCardsInHand();
    float sizeOfCardDivisionOffset = 1; //this offset is for calculating correctly the width and height of a card
    createCardTexture(card);
    sf::Sprite cardSprite(manager.getTexture(card->getCardFullNameAsString()));
    bool isAI = false;


    auto realPlayerPtr = dynamic_cast<RealPlayer*>(player);         //had to "break" inheritance for GUI only. sad day ):
    if (realPlayerPtr == nullptr && player->getName() != "Dealer"){ //Is an AI player
        cardSprite.scale(0.5,0.5);
        sizeOfCardDivisionOffset = 2;
        isAI = true;
    }
    else if(realPlayerPtr != nullptr){ //is a real player
        manager.getTextStatObject("currentSumTextRealPlayer").setString(to_string(player->getCurrentHandSum()));

    }
    else{                      //is dealer
        if (player->getAmountOfCardsInHand() == 2){    //if this is the dealer's second card, then there are special blackjack rules to follow
            sf::Texture backOfCard;
            if(!backOfCard.loadFromFile("C:/Program Files/clionprojects/cardgame/GUIfiles/Sprites/Cards/cardBack_blue5.png")){
                cout << "failed to load back card texture!";
            }
            manager.setDealerOriginalCardTexture(manager.getTexture(card->getCardFullNameAsString()));
            manager.addTexture("backCardTexture", backOfCard);
            cardSprite.setTexture(manager.getTexture("backCardTexture"));
        }
    }
    const sf::Vector2<float>& startingPosition = manager.getPlayerLocation(player->getName());
    sf::Vector2<float> locateCardAt = calculateWhereToDealCard(startingPosition,
                                                               cardSprite, numberOfCards, sizeOfCardDivisionOffset, isAI);

    animateCardDealt(manager.getPlayerLocation("Dealer"), locateCardAt, cardSprite, *windowUsed);
    cardSprite.setPosition(locateCardAt);
    manager.addCardSprite(cardSprite);
}



sf::Vector2<float> calculateWhereToDealCard(const sf::Vector2<float>& startingPosition, const sf::Sprite& cardSprite,
                                            int numberOfCardsInPlayerHand, float sizeOfCardDivisionOffset, bool isAI ){
    --numberOfCardsInPlayerHand;
    sf::Vector2<float> locateAt = startingPosition;
    if(2< numberOfCardsInPlayerHand) {
        if (isAI) {
            locateAt.y += (cardSprite.getLocalBounds().height / sizeOfCardDivisionOffset) + 10;     //add an offset to start a second row
        }
        else{
            locateAt.y -= (cardSprite.getLocalBounds().height/2 / sizeOfCardDivisionOffset) - 30; //real player,adding offset that starts a second row
        }
    }

    numberOfCardsInPlayerHand = numberOfCardsInPlayerHand % 3;
    locateAt.x += (((cardSprite.getLocalBounds().width/sizeOfCardDivisionOffset) + 10 )*numberOfCardsInPlayerHand);
    return  locateAt;
}


string System::realPlayerChooseActionGUI(sf::Vector2<float> positionToLocateButtons){
    /** creating a rectangle that will serve as a button for "Hit" command */
    sf::RectangleShape hitButton;
    hitButton.setPosition(positionToLocateButtons);
    hitButton.setSize(sf::Vector2<float>(100,50));
    hitButton.setOutlineColor(sf::Color::Black);
    hitButton.setFillColor(sf::Color::Green);
    hitButton.setOutlineThickness(3);
    sf::Rect<float> hitButtonRect = hitButton.getGlobalBounds();

    /** creating a rectangle that will serve as a button for "Stand" command */
    sf::RectangleShape standButton;
    standButton.setPosition(positionToLocateButtons.x , positionToLocateButtons.y + hitButton.getLocalBounds().height);
    standButton.setSize(sf::Vector2<float>(100,50));
    standButton.setFillColor(sf::Color::Green);
    standButton.setOutlineColor(sf::Color::Black);
    standButton.setOutlineThickness(3);
    sf::Rect<float> standButtonRect = standButton.getGlobalBounds();

    /** creating text objects for hit and stand buttons */

    const sf::Font& marlboro = manager.getFont("marlboroFont");

    sf::Text hitText("Hit", marlboro);
    hitText.setFillColor(sf::Color::Black);
    hitText.setPosition(positionToLocateButtons.x +hitButton.getLocalBounds().width/2 - hitText.getLocalBounds().width/2,
                        positionToLocateButtons.y + hitButton.getLocalBounds().height/2 - hitText.getLocalBounds().height);

    sf::Text standText("Stand", marlboro);
    standText.setFillColor(sf::Color::Black);
    standText.setPosition(positionToLocateButtons.x + (standButton.getLocalBounds().width /2 - standText.getLocalBounds().width/2),
                          positionToLocateButtons.y + hitButton.getLocalBounds().height + standButton.getLocalBounds().height/2
                          - standText.getLocalBounds().height );

    sf::RenderWindow& window (*windowUsed);
    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                throw System::terminateSystem();   //ending program
            }
            if(event.type == sf::Event::MouseButtonPressed){
                int xCoordinatee = event.mouseButton.x;
                int yCoordiante = event.mouseButton.y;
                if (hitButtonRect.contains(xCoordinatee,yCoordiante )){
                    return "0";
                }
                if (standButtonRect.contains(xCoordinatee,yCoordiante )){
                    return "1";
                }
            }
        }

        /**drawing buttons */
        windowUsed->clear();
        render(*windowUsed);
        windowUsed->draw(hitButton);
        windowUsed->draw(standButton);
        windowUsed->draw(hitText);
        windowUsed->draw(standText);
        windowUsed->display();
    }
    return "0";
}

void System::announce(const string &announcement, float delay) {
    if(!isWithGUI){
        return;
    }
    const sf::Font& marlboro = manager.getFont("marlboroFont");
    sf::Text text(announcement,marlboro, 30);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    text.setPosition(600,440);
    windowUsed->clear();
    render(*windowUsed);
    windowUsed->draw(text);
    windowUsed->display();
    sf::sleep(sf::seconds(delay));
}

void System::flipDealerSecondCard() {
    int amountOfPlayersInGame = PlayersVector.size();
    sf::Sprite& secondDealerCardSprite = manager.getCardSprite(amountOfPlayersInGame*2 + 2) ; //dealer second card
    secondDealerCardSprite.setTexture(manager.getDealerOriginalCardTexture());
}

void System::createCardTexture(Card *&card) {
    sf::Texture cardTexture;
    cardTexture.loadFromFile("C:/Program Files/clionprojects/cardgame/GUIfiles/Sprites/Cards/card" + card->getCardFullNameAsString()+".png");
    manager.addTexture(card->getCardFullNameAsString(), cardTexture);
}


