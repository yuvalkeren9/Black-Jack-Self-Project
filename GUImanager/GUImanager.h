//
// Created by יובל קרן on 8/18/2022.
//

#ifndef MAIN_CPP_GUIMANAGER_H
#define MAIN_CPP_GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>



class GUImanager {
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fontMap;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textureMap;

    std::unordered_map<std::string, std::unique_ptr<sf::Text>> textSetupObjectsMap;

    std::unordered_map<std::string, std::unique_ptr<sf::Text>> textStatsObjectsMap;

    sf::Sprite background;










public:

    /**
     * Function that loads a font into the manager;
     * @param fontName - The name to associate the font with
     * @param fullFilePath - The full path to the font
     *
     * If the function receives a name that is already registered, it does nothing
     */
    void addFont(const std::string& fontName, const std::string& fullFilePath);

    /**
     * Function that returns a font that was loaded beforehand, using the name it was loaded with
     * @param fontName - The name of the font
     * @return Refrence to the font. If the font is not present, a logic exception will be thrown
     */
    const sf::Font& getFont(const std::string& fontName);


    void addTextObject(const std::string &objectName, const sf::Text &textObject, int mapKey);
    sf::Text& getTextObject(const std::string& objectName);

    void drawSetupTextObjects(sf::RenderWindow& window) const {
        for (auto& textObjects : textSetupObjectsMap)
            window.draw(*(textObjects.second));
    }

    void drawStatTextObjects(sf::RenderWindow& window) const;


    void addTexture(const std::string &textureName, const sf::Texture &textureObject);


    void setBackground(const std::string& filePath);
    void drawBackground(sf::RenderWindow& window);
};



//
//bool checkKey (const std::string& key, const std::unordered_map<std::string, std::unique_ptr<sf::Font>> &map);

template <class T>
bool checkKey (const std::string& key, T& map){
    if (map.find(key) == map.end()) {
        return false; //Key is not in the map
    }
    return true; //Key is in the map
}


#endif //MAIN_CPP_GUIMANAGER_H
