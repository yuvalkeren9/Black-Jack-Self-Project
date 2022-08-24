//
// Created by יובל קרן on 8/18/2022.
//

#include "GUImanager.h"

#include <memory>

using namespace std;



void GUImanager::addFont(const string &fontName, const string &fullFilePath) {
    if(checkKey(fontName, fontMap)){
        return;
    }
    unique_ptr<sf::Font> temp (new sf::Font());
    temp->loadFromFile(fullFilePath);
    fontMap[fontName] = move(temp);
}


const sf::Font& GUImanager::getFont(const string &fontName) const{
    if(!checkKey(fontName, fontMap)){
        cout << "Font does not exist" << endl;
        throw logic_error("Font does not exist");
    }
    return *(fontMap.at(fontName));
}

void GUImanager::addTextObject(const string &objectName, const sf::Text &textObject, int mapKey) {
    unique_ptr<sf::Text> temp (new sf::Text(textObject));
    switch (mapKey){
        case 1:
            textSetupObjectsMap[objectName] = move(temp);
            break;
        case 2:
            textStatsObjectsMap[objectName] = move(temp);
            break;
        default:
            cout << "No such map!" << endl;
            throw logic_error("no such map");
    }
}


sf::Text& GUImanager::getTextSetupObject(const string &objectName) {
    if(!checkKey(objectName, textSetupObjectsMap)){
        cout << "TextObject does not exist" << endl;
        throw logic_error("TextObject does not exist");
    }
    return *(textSetupObjectsMap.at(objectName));
}

sf::Text& GUImanager::getTextStatObject(const string &objectName){
    if(!checkKey(objectName, textStatsObjectsMap)){
        cout << "TextObjectStat does not exist" << endl;
        throw logic_error("TextObjectTextObjectStat does not exist");
    }
    return *(textStatsObjectsMap.at(objectName));
}


void GUImanager::drawStatTextObjects(sf::RenderWindow &window) const {
    for (auto& textObjects : textStatsObjectsMap)
        window.draw(*(textObjects.second));
}

void GUImanager::setBackground(const string &filePath) {
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile(filePath)){
        cout <<"Background did not load properly" << endl;
    }
    addTexture("backGroundTexture", backgroundTexture);
    background.setTexture(*textureMap["backGroundTexture"]);
}

void GUImanager::addTexture(const string &textureName, const sf::Texture &textureObject) {
    unique_ptr<sf::Texture> temp (new sf::Texture(textureObject));
    textureMap[textureName] = move(temp);
}

void GUImanager::drawBackground(sf::RenderWindow &window) const {
    window.draw(background);
}

void GUImanager::addPlayer(const string &playerName, float x, float y) {
    unique_ptr<sf::Vector2<float>> temp (new sf::Vector2<float>(x,y));
    playerLocationMap[playerName] = move(temp);
}

void GUImanager::addPlayer(const string &playerName,const sf::Vector2<float>& playerLocation) {
    unique_ptr<sf::Vector2<float>> temp (new sf::Vector2<float>(playerLocation));
    playerLocationMap[playerName] = move(temp);
}


sf::Vector2<float> GUImanager::getPlayerLocation(const string &playerName) const {
    if(!checkKey(playerName, playerLocationMap)){
        cout << "Player Location does not exist" << endl;
        throw logic_error("Player Location does not exist");
    }
    return *(playerLocationMap.at(playerName));
}

void GUImanager::drawPlayerLocations(sf::RenderWindow &window) const {
    sf::CircleShape playerCircle(5);
    for (const auto& player : playerLocationMap){
        playerCircle.setPosition(getPlayerLocation(player.first));
        window.draw(playerCircle);
    }
}


void GUImanager::drawSetupTextObjects(sf::RenderWindow& window) const{
    for (auto& textObjects : textSetupObjectsMap)
        window.draw(*(textObjects.second));
}

void GUImanager::addCardSprite(const sf::Sprite &cardSprite) {
    cardSpritesVector.push_back(std::make_unique<sf::Sprite> (cardSprite));
}

void GUImanager::drawCardSprites(sf::RenderWindow &window) const {
    for (const auto& cards : cardSpritesVector){
        window.draw(*cards);
    }
}

void GUImanager::emptyDeck() {
    while (!cardSpritesVector.empty()){
        cardSpritesVector.pop_back();
    }
}

const sf::Texture &GUImanager::getTexture(const string &textureName) const {
    if(!checkKey(textureName, textureMap)){
        cout << "Texture does not exist" << endl;
        throw logic_error("Texture does not exist");
    }
    return *(textureMap.at(textureName));
}

sf::Sprite& GUImanager::getCardSprite(int num) {
    if (num > cardSpritesVector.size() || num < 0){
        throw range_error("card does not exists");
    }
    --num;
    return *(cardSpritesVector.at(num));
}

void GUImanager::setDealerOriginalCardTexture(const sf::Texture &cardTexture) {
    dealerOriginalTexture = cardTexture;
}
const sf::Texture& GUImanager::getDealerOriginalCardTexture() const{
    return dealerOriginalTexture;
}

