//
// Created by יובל קרן on 8/19/2022.
//

#ifndef MAIN_CPP_TEXTBOX_H
#define MAIN_CPP_TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


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
    void inputLogic(int charTyped);
    void setFont(const sf::Font& font);
    void setPosition(float x, float y);
    void drawTo(sf::RenderWindow& window);
    std::string getString() const;

    void typedOn(const sf::Event& input );

};


#endif //MAIN_CPP_TEXTBOX_H
