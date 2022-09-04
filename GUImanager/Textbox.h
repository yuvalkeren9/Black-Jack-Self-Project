//
// Created by יובל קרן on 8/19/2022.
//

#ifndef MAIN_CPP_TEXTBOX_H
#define MAIN_CPP_TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

/**
 * SFML doesn't have textboxes built in for some reason, so I made a general class that can also be used in the future.
 */
class Textbox {

private:
    static const int BACKSPACE_KEY = 8;
    static const int ENTER_KEY = 13;
    static const int ESCAPE_KEY = 27;

    sf::Text textbox;
    std::ostringstream text;
    int limitOfLength;
    bool hasLimit;
    bool isSelected;
    void deleteLastChar();;

public:
    Textbox();
    explicit Textbox(const sf::Font& font, bool hasLimit = false, int limitOfLength = 15, unsigned int fontSize = 30);

    /**
     * Function that handles adding a char to the string in the textbox
     * @param charTyped
     */
    void inputLogic(int charTyped);

    /**
     * setting font of the textbox
     * @param font font to input
     */
    void setFont(const sf::Font& font);

    /**
     * setter for position
     * @param x x coordinate
     * @param y y coordiante
     */
    void setPosition(float x, float y);

    /**
     * Function that draws the text box to a window
     * @param window the window to draw to
     */
    void drawTo(sf::RenderWindow& window);

    /**
     * getter of the textbox string
     * @return
     */
    std::string getString() const;

    /**
     * Function that handles when user typed on keyboard
     * @param input
     */
    void typedOn(const sf::Event& input );
};


#endif //MAIN_CPP_TEXTBOX_H
