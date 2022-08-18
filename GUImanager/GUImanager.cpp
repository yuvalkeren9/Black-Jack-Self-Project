//
// Created by יובל קרן on 8/18/2022.
//

#include "GUImanager.h"

using namespace std;



void GUImanager::addFont(const string &fontName, const string &fullFilePath) {
    if(checkKey(fontName, fontMap)){
        return;
    }
    unique_ptr<sf::Font> temp (new sf::Font());
    temp->loadFromFile(fullFilePath);
    fontMap[fontName] = move(temp);
}


const sf::Font& GUImanager::getFont(const string &fontName){
    if(!checkKey(fontName, fontMap)){
        cout << "Font does not exist" << endl;
        throw logic_error("Font does not exist");
    }
    return *(fontMap[fontName]);
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

sf::Text& GUImanager::getTextObject(const string &objectName) {
    if(!checkKey(objectName, textSetupObjectsMap)){
        cout << "TextObject does not exist" << endl;
        throw logic_error("TextObject does not exist");
    }
    return *(textSetupObjectsMap[objectName]);
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

void GUImanager::drawBackground(sf::RenderWindow &window) {
    window.draw(background);
}




//bool checkKey (const std::string& key, const std::unordered_map<std::string, std::unique_ptr<sf::Font>> &map) {
//    if (map.find(key) == map.end()) {
//        return false; //Key is not in the map
//    }
//    return true; //Key is in the map
//}

/** helper functions */

