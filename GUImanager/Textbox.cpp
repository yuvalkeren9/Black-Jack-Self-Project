//
// Created by יובל קרן on 8/19/2022.
//

#include "Textbox.h"

using namespace std;



void Textbox::inputLogic(int charTyped) {
    if(charTyped == BACKSPACE_KEY ){
        if(text.str().length() > 0)
            deleteLastChar();
    }
    else if(charTyped == ENTER_KEY){
        return;
    }
    else{
        text << static_cast<char> (charTyped);
    }
    textbox.setString(text.str() + "_");
}

void Textbox::deleteLastChar() {
    string oldString = text.str();
    if (oldString.length() == 0){
        return;
    }
    string newString;
    for (int i = 0; i < oldString.length() - 1; ++i ){
        newString += oldString[i];
    }
    text.str("");
    text << newString;

}

void Textbox::drawTo(sf::RenderWindow &window) {
    window.draw(textbox);
}

void Textbox::typedOn(const sf::Event &input) {
    int charTyped = input.text.unicode;
    if (charTyped == BACKSPACE_KEY){
        deleteLastChar();
        textbox.setString(text.str() + "_");
    }
    else if (charTyped < 128){
        if(hasLimit){
            if (text.str().length() < limitOfLength){
                inputLogic(charTyped);
            }
        }
        else{
            inputLogic(charTyped);
        }
    }
}

void Textbox::setFont(const sf::Font &font) {
    textbox.setFont(font);
}

void Textbox::setPosition(float x, float y) {
    textbox.setPosition(x,y);
}

Textbox::Textbox() : isSelected(true), limitOfLength(15), hasLimit(false){
    textbox.setCharacterSize(30);
}

Textbox::Textbox(const sf::Font &font, bool hasLimit, int limitOfLength, unsigned int fontSize)
: textbox("", font, fontSize), text(""), hasLimit(hasLimit), limitOfLength(limitOfLength) , isSelected(true)  {
}

std::string Textbox::getString() const {
    return text.str();
}
