//
// Created by יובל קרן on 8/18/2022.
//

#ifndef MAIN_CPP_GUIMANAGER_H
#define MAIN_CPP_GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>


/**
 * This is a class that is main job is to handle memory and make the program more efficient.
 * Instead of loading files every frame, the first time some file (image, text, font etc..) is used,
 * it is added the manager which holds a pointer to it, thus avoiding continues loading.
 * Also handles drawing of objects and such
 */
class GUImanager {
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fontMap;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textureMap;
    std::unordered_map<std::string, std::unique_ptr<sf::Text>> textSetupObjectsMap;
    std::unordered_map<std::string, std::unique_ptr<sf::Text>> textStatsObjectsMap;
    std::unordered_map<std::string, std::unique_ptr<sf::Vector2<float>>> playerLocationMap;
    std::vector<std::unique_ptr<sf::Sprite>> cardSpritesVector;
    sf::Sprite background;
    sf::Texture dealerOriginalTexture;

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
    const sf::Font& getFont(const std::string& fontName) const;


    /**
     * Function that adds a text object to the manager to manage.
     * @param objectName name of object
     * @param textObject the text object
     * @param mapKey which type of text object is this - a setup text or stat text
     */
    void addTextObject(const std::string &objectName, const sf::Text &textObject, int mapKey);

    /**
     * a getter of text objects for setup window
     * @param objectName name of the text object to fetch
     * @return the text object
     */
    sf::Text& getTextSetupObject(const std::string& objectName);
    /**
     * a getter of text objects that represent stats
     * @param objectName name of the text object to fetch
     * @return the text object
     */
    sf::Text& getTextStatObject(const std::string &objectName);

    /**
     * function that draw the text objects
     * @param window window to draw into
     */
    void drawSetupTextObjects(sf::RenderWindow& window) const;
    void drawStatTextObjects(sf::RenderWindow& window) const;

    /**
     * Function to add a texture to the manager
     * @param textureName the name of the texture
     * @param textureObject the texture object
     */
    void addTexture(const std::string &textureName, const sf::Texture &textureObject);

    /**
     * getter of texture objects
     * @param textureName the name of the texture object
     * @return texture object
     */
    const sf::Texture& getTexture(const std::string& textureName) const;

    /**
     * Function that sets up the games background
     * @param filePath - path to an image
     */
    void setBackground(const std::string& filePath);
    void drawBackground(sf::RenderWindow& window) const;

    /** Functions for holding and saving the first card the dealer held */
    void setDealerOriginalCardTexture(const sf::Texture& cardTexture);
    const sf::Texture& getDealerOriginalCardTexture() const;


    /**Players related functions*/
    void addPlayer(const std::string& playerName, float x, float y);
    void addPlayer(const std::string &playerName,const sf::Vector2<float>& playerLocation);
    sf::Vector2<float> getPlayerLocation(const std::string& playerName) const;

    /**
     * Draws the player locations on screen. Usefull for adding features.
     * @param window
     */
    void drawPlayerLocations(sf::RenderWindow& window) const;

    void addCardSprite(const sf::Sprite& cardSprite);
    sf::Sprite& getCardSprite(int num);
    void drawCardSprites(sf::RenderWindow& window) const;


    /**
     * Emtying the plkayers hand from a GUI standpoint
     */
    void emptyDeck();
};

/**
 * Template class that checks if a key is in an unordered map
 * @tparam T some map that is from a string to whichever
 * @param key key to check (string omly)
 * @param map any map from string to anything
 * @return whether the key is already used in the map
 */
template <class T>
bool checkKey (const std::string& key, T& map){
    if (map.find(key) == map.end()) {
        return false; //Key is not in the map
    }
    return true; //Key is in the map
}


#endif //MAIN_CPP_GUIMANAGER_H
