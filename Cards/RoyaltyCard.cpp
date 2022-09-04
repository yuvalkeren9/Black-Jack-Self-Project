//
// Created by יובל קרן on 8/5/2022.
//

#include "RoyaltyCard.h"
#include <iostream>

using namespace std;

std::string RoyaltyCard::getCardTypeAsString() const {
    string cardTypeString;
    switch (static_cast<RoyaltyType> (royaltyType)) {
        case 0:
            cardTypeString = "J";
            break;
        case 1:
            cardTypeString ="Q";
            break;
        case 2:
            cardTypeString = "K";
            break;
        default:
            cout << "Not again.. BAD BaD BAD;";
            break;
    }
    return cardTypeString;

}

string RoyaltyCard::getCardFullNameAsString() const {
    return (getCardShapeAsString() + getCardTypeAsString());
}


