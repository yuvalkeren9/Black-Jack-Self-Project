//
// Created by יובל קרן on 8/15/2022.
//
#include <iostream>
#include <functional>
#include "System.h"
#include "Cards/card.h"
#include "Cards/AceCard.h"
#include "Cards/RoyaltyCard.h"
#include "Players/Player.h"
#include <vector>
#include <queue>
#include <sstream>

using namespace std;
/** Helper functions */


void run_test(std::function<bool()> test, std::string test_name)
{
    if(!test()){
        std::cout<< test_name <<" FAILED."<<std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;

}


/**Natural BlackJack tests */

bool naturalBlackJackRealPlayerTest(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("yuval\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Spades, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    System s(move(forTesting), 2);
    s.playRound();
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(1) == 1050){
        return true;
    }
    else{
        cout << "The real player has " << s.getPlayersCurrentMoney(1) << " while he should have had 1050" << endl;
        return false;
    }
}

bool naturalBlackJackAIPlayerTest(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("yuval\n1\n");
    std::cin.rdbuf(input.rdbuf());
    std::queue<std::unique_ptr<Card>> forTesting;
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Spades, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    System s(move(forTesting), 2);
    s.playRound();
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(2) == 1050){
        return true;
    }
    else{
        cout << "The AI player has " << s.getPlayersCurrentMoney(1) << " while he should have had 1050" << endl;
        return false;
    }
}

bool naturalBlackJackDealerTest(){

}

bool naturalBlackJackDealerAndPlayer(){}

int main(){
    run_test(naturalBlackJackRealPlayerTest, "Natural BlackJack for real player");
    run_test(naturalBlackJackAIPlayerTest, "Natural Black Jack AI Player Test");
}