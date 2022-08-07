//
// Created by יובל קרן on 8/5/2022.
//

#include "System.h"


#include "card.h"
#include <fstream>
#include <memory>
#include "RoyaltyCard.h"
#include "AceCard.h"
#include "NumiricalCard.h"
#include<random>
#include <algorithm>
#include <chrono>


using namespace std;

//queue<std::unique_ptr<Card>> createCardDeck(const string& fileName){
//    ifstream source(fileName);
//    queue<unique_ptr<Card>> tempQueue;
////    if(!source){
////        throw DeckFileNotFound();
////    }
//    string cardName;
//    while (getline(source, cardName, ' ')){                   //reading the Card name from the cards file
//        string cardType;
//        getline(source, cardType);                                  //reading the Card type from the cards file
//        tempQueue.push(getPointerToNewCard(cardName, cardType));
//    }
//    return tempQueue;
//}
//
//unique_ptr<Card> getPointerToNewCard(const std::string& cardName, const std::string& cardType){
//    const string numbers = ("0123456789");
//    if (cardName.find_first_not_of(numbers) != string::npos){     //then this is not a numerical card
//        if (cardName == "Ace"){
//            return new(AceCard());                  //TODO
//        }
//        else{
//            if ()
//        }
//    }
//
//
//}


vector<std::unique_ptr<Card>> createCardDeck(int numOfDecks){
    static int smallestCardValue = 2;
    static int largestCardValue = 10;
    static int amountOfDiffrentCardTypes = 4;

    vector<unique_ptr<Card>> tempVector;

    // TODO : make sure numOfDecks is legal
    for (int i=0; i < numOfDecks; ++i){                 //creating the 2-10 regular cards
        for(int j=smallestCardValue; j <= largestCardValue; ++j){
            for (int p = 1; p <= amountOfDiffrentCardTypes; ++p) {
                tempVector.push_back(make_unique<Card> (j, intToCardTypeAdapter(p)));
            }
        }               //the royal house is seperated from the regular cards because I wanted to experiment with make unique

        for (int p = 1; p <= amountOfDiffrentCardTypes; ++p) {
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), Jack)));
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), Queen)));
            tempVector.push_back(unique_ptr<Card> (new RoyaltyCard(intToCardTypeAdapter(p), King)));
            tempVector.push_back(unique_ptr<Card> (new AceCard(intToCardTypeAdapter(p))));
        }
        unsigned num = chrono::system_clock::now().time_since_epoch().count();
        shuffle(tempVector.begin(), tempVector.end(), default_random_engine(num));
    }
    return tempVector;
}