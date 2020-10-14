#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

std::string hitstick;
std::string yesno;

int cardTemp{ 0 };
void printCards(std::vector<int> array);
int handTotal(std::vector<int> array);
int playercapital = 100;
int dealercapital = 100;
int bet;

int main()
{
    int dealcards();
    void youlose();
    void youwin();
    void dealerplay(std::vector<int> pHand, std::vector<int> dHand);
  
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (true) {
        std::vector<int> pHand{};
        std::vector<int> dHand{};

        system("cls");
        //menu
        std::cout << "\tBlackjack\n";
        std::cout << "\t*********\n\n";
        std::cout << "Welcome to Blackjack\n\n";
        std::cout << "Your capital is " << playercapital << "$\n";
        std::cout << "dealers capital is " << dealercapital << "$\n\n";
        if (playercapital <= 0) {
            //player broke
            std::cout << "You are broke, get outta here!\n\n";
            system("pause");
            exit(0);
        }
        if (dealercapital <= 0) {
            //dealer broke
            std::cout << "Congratulations! You have bested me.\n\n";
            system("pause");
            exit(0);
        }
        //placing bet
        std::cout << "Place your bet, has to be 10 or higher: \n";
        std::cin >> bet;
        while (bet < 10) {
            std::cout << "bet has to be higher than 10\n";
            std::cin >> bet;
        }
        while (bet > playercapital) {
            //bet higher than capital
            std::cout << "You dont have enough money\n";
            std::cout << "do you want to place a new bet?(EG:Y/N)\n";
            std::cin >> yesno;
            if (yesno == "Y" || yesno == "y") {
            std::cout << "Place your bet, has to be 10 or higher: \n";
            std::cin >> bet;
            }
                while (std::cin.fail() == true) {
                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    std::cout << "Place your bet, has to be 10 or higher: \n";
                    std::cin >> bet;
                }
            if (yesno == "N" || yesno == "n") {
                std::cout << "Have a good day!\n\n";
                system("pause");
                exit(0);
            }
        }
        //first 2 cards
        std::cin.get();
        std::cout << "\n";
        cardTemp = dealcards();
        if (cardTemp == 1) {
            std::cout << "\nyou got an Ace, Do you want to keep it as 11 or 1: \n";
            cardTemp = 0;
            while (cardTemp != 1 && cardTemp != 11) {
                std::cin >> cardTemp;
            }
        }
        pHand.push_back(cardTemp);

        cardTemp = dealcards();
        if (cardTemp == 1) {
            std::cout << "\nyou got an Ace, Do you want to keep it as 11 or 1: \n";
            cardTemp = 0;
            while (cardTemp != 1 && cardTemp != 11) {
                std::cin >> cardTemp;
            }
        }
        pHand.push_back(cardTemp);

        while (true) {
            //card total Bust or blackjack
            printCards(pHand);
            std::cout << "Your card total is: " << handTotal(pHand) << "\n\n";
            if (handTotal(pHand) > 21) {
                system("pause");
                youlose();
                break;
            }
            if (handTotal(pHand) == 21) {
                system("pause");
                youwin();
                break;
            }
            //hit or stick
            std::cout << "\n";
            std::cout << "Do you want to 'Hit' or 'Stick'?(Eg:H/S)\n";
            std::cin >> hitstick;
            if (hitstick == "H" || hitstick == "h") {
                cardTemp = dealcards();
                if (cardTemp == 1) {
                    std::cout << "\nYou got an Ace, Do yu want to keep it as 11 or 1: \n";
                    cardTemp = 0;
                    while (cardTemp != 1 && cardTemp != 11) {
                        std::cin >> cardTemp;
                    }
                }
                pHand.push_back(cardTemp);
            }
            if (hitstick == "S" || hitstick == "s") {
                dealerplay(pHand, dHand);
                break;
            }
        }
    }
}

int dealcards() {
    //random card generator from 1-13 if card > 10 then card = 10
    int card{ 0 };
    card = rand() % 13 + 1;
    if (card > 10) {
        card = 10;
    }
    return card;
}

void youlose() {
    //Function for Bust
    system("cls");
    std::cout << "Blackjack\n";
    std::cout << "*********\n\n";
    std::cout << "Sorry you have bust!\n\n";
    playercapital = playercapital - bet;
    dealercapital = dealercapital + bet;
    system("pause");
}

void youwin() {
    //Function for Blackjack
    system("cls");
    std::cout << "Blackjack\n";
    std::cout << "*********\n\n";
    std::cout << "Congratulation you got BLACKJACK, you have won!\n\n";
    playercapital = playercapital + bet;
    dealercapital = dealercapital - bet;
    system("pause");
}

void dealerplay(std::vector<int> pHand, std::vector<int> dHand) 
{
    //dealer plays
    system("cls");

    while (true) {
        system("cls");
        std::cout << "Blackjack\n";
        std::cout << "*********\n\n";
        std::cout << "Dealers turn:\n";
        std::cout << "Your Cards: \n";
        printCards(pHand);
        std::cout << "Your Total: " << handTotal(pHand);
        std::cout << "\n\nDealers Cards: \n";
        printCards(dHand);
         std::cout << "Dealer Total: " << handTotal(dHand) << "\n\n";


        //check totals:
        if (handTotal(dHand) == handTotal(pHand)){
            //TIE
            std::cout << "ITS A TIE\n\n";
            system("pause");
            return;
        }

        if (handTotal(dHand) > handTotal(pHand) && handTotal(dHand) <= 21){
            std::cout << "\n\nYOU LOSE!\n\n";
            //player lose
            //lose money
            playercapital = playercapital - bet;
            dealercapital = dealercapital + bet;
            system("pause");
            return;
        }

        if (handTotal(dHand) > 21){
            std::cout << "The dealer busts, you win!\n";
            //player win
            //win money
            std::cout << "\n\nYOU WIN!\n\n";
            playercapital = playercapital + bet;
            dealercapital = dealercapital - bet;
            system("pause");
            return;
        }

        //dealer draws cards

        std::chrono::milliseconds dealerWait(1500);
        std::this_thread::sleep_for(dealerWait);

        cardTemp = dealcards();
        if (cardTemp == 1)
        {
            if ((handTotal(dHand) + 11) > 21)
            {
                cardTemp = 1;
            } else
            {
                cardTemp = 11;
            }
        }
        dHand.push_back(cardTemp);
    }
    return;
}

int handTotal(std::vector<int> array)
{
    int total{ 0 };
    for(int i = 0; i < array.size(); i++)
    {
        total += array.at(i);
    }
    return total;
}

void printCards(std::vector<int> array)
{
    for(int i = 0; i < array.size(); i++)
    {
        std::cout << "Card [" << i+1 << "]: " << array.at(i) << std::endl;
    }
}