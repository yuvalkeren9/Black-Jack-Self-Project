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


bool run_test(std::function<bool()> test, std::string test_name)
{
    if(!test()){
        std::cout<< test_name <<" FAILED."<<std::endl;
        std::cout << std::endl;
        return false;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;
    return true;

}


/**Natural BlackJack tests */

bool naturalBlackJackRealPlayerTest(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Yuval\n");
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
    std::istringstream input("Suki\n1\n");
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
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Katara\n1\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Spades, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    System s(move(forTesting), 2);
    s.playRound();


    std::cin.rdbuf(orig);

    if (s.getPlayersCurrentMoney(1) == 900 && s.getPlayersCurrentMoney(2) == 900){
        return true;
    }
    else{
        cout << "The dealer had a natural blackjack, but the bets didnt go as instructed" << endl;
        s.printBankDetails();
        return false;
    }

}

bool naturalBlackJackDealerAndPlayer(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Aang\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));

    System s(move(forTesting), 2);
    s.playRound();


    std::cin.rdbuf(orig);

    if (s.getPlayersCurrentMoney(1) == 1050 && s.getPlayersCurrentMoney(2) == 900){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }
}

/** end of round reset test */

bool twoRoundsInARowTest(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Aang\n1\n0\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;

    //cards for first round. Real player loses with 16, AI wins with 20, dealer loses with 18
    forTesting.push(std::unique_ptr<Card> (new Card(5,Clubs)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new Card(8,Clubs)) );

    //cards for second round. Real player has 20, AI busts with 23, dealer loses with 18
    forTesting.push(std::unique_ptr<Card> (new Card(5,Clubs)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new Card(5,Clubs)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new Card(8,Clubs)) );
    forTesting.push(std::unique_ptr<Card> (new Card(5,Clubs)) );
    forTesting.push(std::unique_ptr<Card> (new Card(8,Clubs)) );

    System s(move(forTesting), 2);
    s.playRound();
    if(s.getPlayersCurrentMoney(1) != 900 && s.getPlayersCurrentMoney(2) != 1100){
        cout << "Test failed in the first round.. Shame on you" << endl;
        s.printBankDetails();
        std::cin.rdbuf(orig);
        return false;
    }
    s.playRound();
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(1) == 1000 && s.getPlayersCurrentMoney(2) == 1000){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }

}

bool twoRoundsShuffleDeckTest(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Sokka\n1\n1\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;
    //cards for first round. Real player loses with 18, AI wins with 20, dealer has 19
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new Card(9, Hearts)));

    //cards for second round. Player loses with 19, AI loses with 18, dealer has 20
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));

    System s(move(forTesting), 2);
    s.playRound();
    s.playRound();
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(1) == 800 && s.getPlayersCurrentMoney(2) == 1000){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }
}



bool changeAceFrom11ToOne(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("Anna Zack\n0\n0\n0\n1\n");
    std::cin.rdbuf(input.rdbuf());

    std::queue<std::unique_ptr<Card>> forTesting;
    //cards for first round. Real player wins with 20, AI wins with 20, dealer has 19
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)));
    forTesting.push(std::unique_ptr<Card> (new Card(9, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new Card(5, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new Card(5, Hearts)));

    System s(move(forTesting), 2);
    s.playRound();
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(1) == 1100 && s.getPlayersCurrentMoney(2) == 1100){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }
}

bool cardsNotDealtToDeadPeople(){
        std::streambuf* orig = std::cin.rdbuf();
        std::istringstream input("Noa Kirel\n");
        std::cin.rdbuf(input.rdbuf());
        std::queue<std::unique_ptr<Card>> forTesting;

        forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
        forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
        forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
        forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
        forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
        forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
        forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
        forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
        System s(move(forTesting), 3);
        for (int i=1; i<=11; ++i){
            cout << "start of round " << i <<endl <<endl;
            s.playRound();
        }
        std::cin.rdbuf(orig);
        if (s.getPlayersCurrentMoney(1) == 1550){
            return true;
        }
        else{
            cout << "Test failed" << endl;
            s.printBankDetails();
            return false;
        }
}

bool singleWinner(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("John Travolta\n");
    std::cin.rdbuf(input.rdbuf());
    std::queue<std::unique_ptr<Card>> forTesting;

    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    System s(move(forTesting), 2);
    int i= 1;
    while(true){
        cout << "start of round " << i <<endl <<endl;
        if(s.playRound())
            break;
        ++i;
    }
    std::cin.rdbuf(orig);
    if (s.getPlayersCurrentMoney(1) == 1500){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }
}

bool tieBetweenPlayers(){
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("John Travolta\n");
    std::cin.rdbuf(input.rdbuf());
    std::queue<std::unique_ptr<Card>> forTesting;

    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Diamonds, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new Card(8, Hearts)));
    forTesting.push(std::unique_ptr<Card> (new RoyaltyCard(Clubs, Jack)) );
    forTesting.push(std::unique_ptr<Card> (new AceCard(Hearts)));
    System s(move(forTesting), 2);
    int i= 1;
    while(true){
        cout << "start of round " << i <<endl <<endl;
        if(s.playRound())
            break;
        ++i;
    }
    std::cin.rdbuf(orig);
    if (i == 10){
        return true;
    }
    else{
        cout << "Test failed" << endl;
        s.printBankDetails();
        return false;
    }

}

int main(){
    if(!run_test(naturalBlackJackRealPlayerTest, "Natural BlackJack for real player"))
        return 1;
    if(!run_test(naturalBlackJackAIPlayerTest, "Natural Black Jack AI Player Test"))
        return 1;
    if(!run_test(naturalBlackJackDealerTest, "Natural Black Jack Dealer test"))
        return 1;
    if(!run_test(naturalBlackJackDealerAndPlayer, "Natural Black Jack Dealer And Player"))
        return 1;
    if(!run_test(twoRoundsInARowTest,"Two rounds in a Row test"))
        return 1;
    if(!run_test(twoRoundsShuffleDeckTest,"Was deck shuffled as expected"))
        return 1;
    if(!run_test(changeAceFrom11ToOne, "Checking if aces change from 11 to one when needed"))
        return 1;
    if(!run_test(cardsNotDealtToDeadPeople,"No cards were dealt to dead people"))
        return 1;
    if(!run_test(singleWinner,"Single Winner"))
        return 1;
    if(!run_test(tieBetweenPlayers,"Tie between Players"))
        return 1;
}