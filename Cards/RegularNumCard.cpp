//
// Created by יובל קרן on 8/17/2022.
//

#include "RegularNumCard.h"
#include <string>

using namespace std;


std::string RegularNumCard::getCardFullNameAsString() const {
    return (getCardShapeAsString() + to_string(getValue()));
}
