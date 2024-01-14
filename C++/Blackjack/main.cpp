#include<iostream>
#include <string>
#include <iomanip>
#include <time.h>      
#include <stdlib.h>   
#include <locale>
#include <vector>
#include <algorithm>
#include "blackjack.h"
string userAnswer = "P";
string gameChoice;

int main() 
{
    BlackJackGame BlJa;
    BlJa.createDeckImage();
    
    // Allows user to choose game
    while (userAnswer != "Q")
    {
    userAnswer = "P";
    cout << "--------------------------------------------------------------------\n";
    cout << "|BELOW IS A LIST OF GAME OPTIONS                                 |\n";
    cout << "|'1' = BLACKJACK                                                 |\n";
    cout << "|ENTER YOUR GAME CHOICE                                          |\n";
    cout << "|USER ANSWER: ";
    cin >> gameChoice;
    cout << "--------------------------------------------------------------------\n";
    transform(gameChoice.begin(), gameChoice.end(), gameChoice.begin(), ::toupper);

    while (gameChoice == "1" && userAnswer == "P")
    {
      BlJa.playBlackjack();
    }
    }
    cout << "--------------------------------------------------------------------\n";
}