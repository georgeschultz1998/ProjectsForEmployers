#include "deck.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <locale>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

class BlackJackGame {
private:
  // Definies variables used in program.
  string userAnswer = "P";
  string gameChoice;

  // Creating each card symbol (Heart, Diamond, Club, Spade)
  string spade = "\xe2\x99\xa4";
  string diamond = "\xe2\x99\xa2";
  string club = "\xe2\x99\xa7";
  string heart = "\xe2\x99\xa1";
  string blank = " ";
  string title;
  string cardImage[56];
  int cardValue[51];
  int cardNumber[20];
  int numberOfCards = 4;
  int userScore;
  int dealerScore;
  deckOfCards aDeck;
  int numPlayed;

public:
  void createDeckImage();
  void repeatString(string s, int n);
  void printTitle(string);
  void printBlackjackUser(void);
  void computeBlackjackScore(void);
  void checkBlackjackScore(void);
  void blackjackNewCard(void);
  void printBlackjackSeeResultsTitle(void);
  void assignCardValues(void);
  void playBlackjack(void);
};

//------------------------------------------------------------------------------
// Function to create all images for deck.
//------------------------------------------------------------------------------
inline void BlackJackGame::createDeckImage(void) {
  // Creates all images for spade cards
  cardImage[0] = "|A" + spade + "   |";
  cardImage[1] = "|2" + spade + "   |";
  cardImage[2] = "|3" + spade + "   |";
  cardImage[3] = "|4" + spade + "   |";
  cardImage[4] = "|5" + spade + "   |";
  cardImage[5] = "|6" + spade + "   |";
  cardImage[6] = "|7" + spade + "   |";
  cardImage[7] = "|8" + spade + "   |";
  cardImage[8] = "|9" + spade + "   |";
  cardImage[9] = "|10" + spade + "  |";
  cardImage[10] = "|J" + spade + "   |";
  cardImage[11] = "|Q" + spade + "   |";
  cardImage[12] = "|K" + spade + "   |";

  // Creates all images for diamond cards
  cardImage[13] = "|A" + diamond + "   |";
  cardImage[14] = "|2" + diamond + "   |";
  cardImage[15] = "|3" + diamond + "   |";
  cardImage[16] = "|4" + diamond + "   |";
  cardImage[17] = "|5" + diamond + "   |";
  cardImage[18] = "|6" + diamond + "   |";
  cardImage[19] = "|7" + diamond + "   |";
  cardImage[20] = "|8" + diamond + "   |";
  cardImage[21] = "|9" + diamond + "   |";
  cardImage[22] = "|10" + diamond + "  |";
  cardImage[23] = "|J" + diamond + "   |";
  cardImage[24] = "|Q" + diamond + "   |";
  cardImage[25] = "|K" + diamond + "   |";

  // Creates all images for club cards
  cardImage[26] = "|A" + club + "   |";
  cardImage[27] = "|2" + club + "   |";
  cardImage[28] = "|3" + club + "   |";
  cardImage[29] = "|4" + club + "   |";
  cardImage[30] = "|5" + club + "   |";
  cardImage[31] = "|6" + club + "   |";
  cardImage[32] = "|7" + club + "   |";
  cardImage[33] = "|8" + club + "   |";
  cardImage[34] = "|9" + club + "   |";
  cardImage[35] = "|10" + club + "  |";
  cardImage[36] = "|J" + club + "   |";
  cardImage[37] = "|Q" + club + "   |";
  cardImage[38] = "|K" + club + "   |";

  // Creates all images for heart cards
  cardImage[39] = "|A" + heart + "   |";
  cardImage[40] = "|2" + heart + "   |";
  cardImage[41] = "|3" + heart + "   |";
  cardImage[42] = "|4" + heart + "   |";
  cardImage[43] = "|5" + heart + "   |";
  cardImage[44] = "|6" + heart + "   |";
  cardImage[45] = "|7" + heart + "   |";
  cardImage[46] = "|8" + heart + "   |";
  cardImage[47] = "|9" + heart + "   |";
  cardImage[48] = "|10" + heart + "  |";
  cardImage[49] = "|J" + heart + "   |";
  cardImage[50] = "|Q" + heart + "   |";
  cardImage[51] = "|K" + heart + "   |";

  // Creates Image for backside of card
  cardImage[52] = "______\n|?????|\n|?????|\n|?????|\n|_____|\n";
}
//
//
inline void BlackJackGame::repeatString(string s, int n) {
  while (n > 0) {
    cout << s;
    n--;
  }
}

//------------------------------------------------------------------------------
// Title for game
//------------------------------------------------------------------------------
inline void BlackJackGame::printTitle(string) {

  // First Line
  cout << string(50, '-') << endl;

  // Second Line
  cout << "|";
  for (int i = 0; i < 5; i++) {
    repeatString(spade, 6);
    repeatString(diamond, 6);
  }
  repeatString(spade, 6);
  cout << "|" << endl;

  // Third Line
  cout << "|";
  repeatString(spade, 6);
  repeatString(diamond, 6);
  repeatString(blank, 42);
  repeatString(club, 6);
  repeatString(heart, 6);
  cout << "|" << endl;

  // Fourth Line
  cout << "|";
  repeatString(spade, 6);
  repeatString(diamond, 6);
  cout << title;
  repeatString(club, 6);
  repeatString(heart, 6);
  cout << "|" << endl;

  // Fifth Line
  cout << "|";
  repeatString(spade, 6);
  repeatString(diamond, 6);
  repeatString(blank, 42);
  repeatString(club, 6);
  repeatString(heart, 6);
  cout << "|" << endl;

  // Sixth Line
  cout << "|";
  repeatString(club, 6);
  repeatString(heart, 6);
  repeatString(club, 6);
  repeatString(heart, 6);
  repeatString(club, 6);
  repeatString(heart, 6);
  repeatString(club, 6);
  repeatString(heart, 6);
  repeatString(club, 6);
  repeatString(heart, 6);
  repeatString(club, 6);
  cout << "|" << endl;
  repeatString("-", 50);
  cout << endl;
}

//------------------------------------------------------------------------------
// Prints a blackjackusers current cards and score
//------------------------------------------------------------------------------
inline void BlackJackGame::printBlackjackUser(void) {
  // Displays User Score and User Score
  cout << string(50, '-') << endl;
  cout << "|      YOUR CARDS      |     YOUR SCORE: " << userScore << "      |"
       << "\n";
  cout << string(50, '-') << endl;

  for (int i = 2; i < numberOfCards; i++) {
    cout << " _____ ";
  }
  cout << "\n";

  for (int i = 2; i < numberOfCards; i++) {
    cout << cardImage[cardNumber[i]];
  }
  cout << "\n";

  for (int i = 2; i < numberOfCards; i++) {
    cout << "|     |";
  }
  cout << "\n";

  for (int i = 2; i < numberOfCards; i++) {
    cout << "|     |";
  }
  cout << "\n";

  for (int i = 2; i < numberOfCards; i++) {
    cout << "|_____|";
  }
  cout << "\n";
}

//------------------------------------------------------------------------------
// Computes the blackjack score of user.
//------------------------------------------------------------------------------
inline void BlackJackGame::computeBlackjackScore(void) {
  // resets Userscore to 0 for counting.
  userScore = 0;
  cout << "compute user score" << endl;
  // Reduces ace value from 11 to 1 when ace causes score to rise above 21
  // first compute the score
  for (int i = 2; i < numberOfCards; i++) {
    userScore += cardValue[cardNumber[i]];
  }

  cout << "Score==" << userScore << endl;
  cout << "Now reduce it if there are aces" << endl;
  int i = 2;
  while (userScore > 21 and i < numberOfCards) {
    if (cardValue[cardNumber[i]] == 11) {
      userScore -= 10; // reduce the score by 10
    }
    i++;
  }
}

//------------------------------------------------------------------------------
// Function that checks if user score is at 21 or above it.
//------------------------------------------------------------------------------
inline void BlackJackGame::checkBlackjackScore(void) {
  // Ends game if user hits 21
  if (userScore == 21) {
    cout << "\n--------------------------------------------------"
         << "\n";
    cout << "|          GAME OVER. YOUR SCORE IS 21.          |\n";
    userAnswer = "NO";
  }
  // Ends game if user goes above 21
  else if (userScore > 21) {
    cout << "\n--------------------------------------------------"
         << "\n";
    cout << "|       GAME OVER. YOUR SCORE IS OVER 21.        | \n";
    userAnswer = "NO";
  }
}

//------------------------------------------------------------------------------
// Asks user if they would like new card and prints it out if they say yes.
//------------------------------------------------------------------------------
inline void BlackJackGame::blackjackNewCard(void) {
  if (userScore < 21) {
    // Asks user if they want new card
    cout << "\n--------------------------------------------------"
         << "\n";
    cout << "|WOULD YOU LIKE ANOTHER CARD? ('YES' OR 'NO').   |\n";
    cout << "|YOUR ANSWER: ";
    cin >> userAnswer;
    transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(),
              ::toupper);

    // Validates that response is Yes, No, Quit, or Q
    while (userAnswer != "NO" && userAnswer != "YES" && userAnswer != "QUIT" &&
           userAnswer != "Q") {
      cout << "|INVALID RESPONSE. POSSIBLE ANSWERS ARE 'YES' OR 'NO'\n";
      cout << "|YOUR ANSWER: ";
      cin >> userAnswer;
      transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(),
                ::toupper);
    }
    // Gvies user a new card if they answer Yes when asked for one.
    if (userAnswer == "YES") {
      // create a new card...
      card atemp = aDeck.dealCard();
      cardNumber[numberOfCards] = atemp.number();
      numberOfCards++;

      // cardNumber[numberOfCards + 1] = rand() % 51 + 0;
      cout << "--------------------------------------------------"
           << "\n";
      cout << "|             BELOW IS YOUR NEW CARD             |\n";
      cout << "--------------------------------------------------\n";
      cout << "______ \n"
           << cardImage[cardNumber[numberOfCards - 1]] << "\n"
           << "|     |\n"
           << "|     |\n"
           << "|_____|\n\n";
      // numberOfCards=aDeck.number();
    }
  }
}

//------------------------------------------------------------------------------
// Prints results page based on game results
//------------------------------------------------------------------------------
inline void BlackJackGame::printBlackjackSeeResultsTitle(void) {
  // this score is in error if two aces = 22 occurs
  // also - the dealer gets to cards too
  dealerScore = cardValue[cardNumber[0]] + cardValue[cardNumber[1]];
  if (dealerScore > 21) {
    // check for aces - if two aces - then remove score for one
    if (cardValue[cardNumber[0]] == 11 and cardValue[cardNumber[1]] == 11) {
      dealerScore -= 10; // subtract 10.
    }
  }

  cout << "dealerScore1 " << dealerScore << endl;

  if (dealerScore < 17) {
    // add cards til > 17
  }

  // Outputs message for if User Wins
  if (userScore < 22 && userScore > dealerScore) {
    cout << "--------------------------------------------------"
         << "\n";
    cout << "\n\n--------------------------------------------------------------"
            "-----"
         << "\n";
    cout
        << "|              YOU WON! SEE RESULTS BELOW!                        |"
        << " \n";
  }

  // Outputs message for if User Wins
  else if (userScore < 22 && userScore == dealerScore) {
    cout << "--------------------------------------------------"
         << "\n";
    cout << "\n\n--------------------------------------------------------------"
            "-----"
         << "\n";
    cout
        << "|             TIE GAME! SEE RESULTS BELOW!                        |"
        << " \n";
  }
  // Outputs message for if User Loses
  else {
    cout << "--------------------------------------------------"
         << "\n";
    cout << "\n\n--------------------------------------------------------------"
            "-----"
         << "\n";
    cout
        << "|             DEALER WON! SEE RESULTS BELOW!                      |"
        << " \n";
  }
}

/*
 Assign the Card Values Function

*/

inline void BlackJackGame::assignCardValues(void) {
  // Sets values for each card
  int x = 1;
  int y = 11;

  // set cardvalue for numeric cards
  for (int i = 0; i < y; i++) {
    cardValue[i] = x;
    cardValue[i + 13] = x;
    cardValue[i + 26] = x;
    cardValue[i + 39] = x;
    x++;
  }

  // set cardvalue for facecards to 10
  for (int i = 0; i < 3; i++) {
    cardValue[i + 10] = 10;
    cardValue[i + 23] = 10;
    cardValue[i + 36] = 10;
    cardValue[i + 49] = 10;
  }

  // set cardvalue for ace's to 11 (but could be 1)
  cardValue[0] = 11;
  cardValue[13] = 11;
  cardValue[26] = 11;
  cardValue[39] = 11;
}
//------------------------------------------------------------------------------
// Function that does vital blackjack requirements
//------------------------------------------------------------------------------

inline void BlackJackGame::playBlackjack(void) {
  // Welcome Title
  title = "            WELCOME TO BLACKJACK          ";
  printTitle(title);

  // Resets userScore for score keeping purposes
  userScore = 0;

  assignCardValues();

  // numPlayed=0; // played cards
  numberOfCards = 0;
  // Gives dealer 2 random cards

  // Need to maintain all cards dealt array and card deck array
  // create an array of cards - then subtract the card from the deck
  // and add it to the dealt card array
  // reduce the number of cards from 51 and increase dealt by 1
  // this will eliminate duplicats cards.
  // use the card-deck class for this section
  aDeck.shuffle();

  // srand (time(NULL));
  card temp;
  // cardNumber[0] = rand() % 51 + 0;
  temp = aDeck.dealCard();
  cout << temp.print() << endl;
  cardNumber[numberOfCards] = temp.number();
  numberOfCards++;
  // cardNumber[1] = rand() % 51 + 0;
  temp = aDeck.dealCard();
  cout << temp.print() << endl;
  cardNumber[numberOfCards] = temp.number();
  numberOfCards++;

  // Displays dealers two cards. One visible, one hidden.
  cout << "---------------------------------------------------"
       << "\n";
  cout << "|      DEALER CARDS      |    DEALER SCORE: ???   |"
       << " \n";
  cout << "---------------------------------------------------\n";
  cout << "______ ______ \n"
       << cardImage[cardNumber[0]] << "|?????|"
       << "\n"
       << "|     ||?????|\n"
       << "|     ||?????|\n"
       << "|_____||_____|\n\n";

  // Gives user 2 random cards.
  // cardNumber[2] = rand() % 51 + 0;
  // cardNumber[3] = rand() % 51 + 0;
  temp = aDeck.dealCard();
  cardNumber[numberOfCards] = temp.number();
  numberOfCards++;
  cout << temp.print() << endl;
  temp = aDeck.dealCard();
  cardNumber[numberOfCards] = temp.number();
  numberOfCards++;
  cout << temp.print() << endl;
  cout << "nCards " << numberOfCards << endl;

  // numberOfCards should be 4 at this point
  // Sets while loop that ensures user remains in game until they stop asking
  // for cards, quit, or have score go over 21.
  while (userAnswer != "NO" && userScore < 22 && userAnswer != "QUIT" &&
         userAnswer != "Q") {
    // Adds to number of cards count each time user asks for another card.
    // numberOfCards++;
    cout << "number of cards played from deck" << aDeck.number() << endl;
    // numberOfCards=aDeck.number();

    // Computes current user score
    computeBlackjackScore();

    // Calls function which prints users score and cards
    printBlackjackUser();

    // Checks if blackjack score has met or exceeded 21
    checkBlackjackScore();

    // Asks user if they want new card when their current score is less than 21
    blackjackNewCard();
  }

  // Prints out see results title based on outcome of game
  printBlackjackSeeResultsTitle();

  // Outputs Dealer final cards and score
  cout << "-------------------------------------------------------------------"
       << "\n";
  cout << "|      DEALER CARDS      |    DEALER SCORE: " << dealerScore
       << "   |\n";
  cout << "--------------------------------------------------\n";
  cout << "______ ______ \n"
       << cardImage[cardNumber[0]] << cardImage[cardNumber[1]] << "\n"
       << "|     ||     |\n"
       << "|     ||     |\n"
       << "|_____||_____|\n\n";

  printBlackjackUser();

  while (userAnswer != "P" && userAnswer != "Q" && userAnswer != "M") {
    cout << "\n\n--------------------------------------------------------------"
            "-----\n";
    cout << "|NOW THAT GAME IS OVER, BELOW ARE YOUR NEXT OPTIONS.             "
            "|\n";
    cout << "|PLAY AGAIN = P, MAIN MENU = M, QUIT = Q                         "
            "|\n";
    cout << "|YOUR ANSWER: ";
    cin >> userAnswer;
    transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(),
              ::toupper);
    cout << "------------------------------------------------------------------"
            "--\n";
  }
  cout << "|                                                                 "
          "|\n";
  cout << "|                                                                 "
          "|\n";
  // numberOfCards = 3;
  userScore = 0;
}