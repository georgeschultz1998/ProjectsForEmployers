/* So far this program generates a card deck, shuffles it, and outputs the card
//Header
file----------------------------------------------------------------------------------------
*/
#include <array>
// always include iostream
#include <iostream>
// random number generator
#include <cstdlib>
// random number generator
#include <ctime>

#include <algorithm>

using namespace std;

// Initilize constant variables
const int SIZE = 52;

// create a class called card
class card {
public:
  // default constructer
  card();
  // constructer with parameters
  card(string cardFace, string cardSuit);
  // print function
  string print();

  int value();

  int number();

private:
  // create two card variables face and suit
  string face;
  string suit;
  // put all the face values in an array as strings
  string faces[13] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                      "8",   "9", "10", "Jack", "Queen", "King"};
  // put all the suit values in an array as strings
  string suits[4] = {"Spades", "Diamonds", "Clubs", "Hearts"};
};

// create a class for deckOfCards
class deckOfCards {
public:
  // Default constructor: assigns the 52 cards to deck
  deckOfCards();
  // shuffles the deck once all the cards are assigned
  void shuffle();
  // deals out one card from the deck of 52, refrences class card
  card dealCard();
  int size();
  void printDeck();
  int number();

private:
  // variable card with a pointer to deck
  array<card, SIZE> deck; // an array of cards of size SIZR
  // keep track of what card you are dealing with
  int currentCard;
  // put all the face values in an array as strings
  string faces[13] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                      "8",   "9", "10", "Jack", "Queen", "King"};
  // put all the suit values in an array as strings
  string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
};

//------------------------------------------------------------------------------------------------//
// file implementation

// default constructor
inline card::card() {
  // nothing goes in here
}
// constructor with two parameters
inline card::card(string cardFace, string cardSuit) {
  // assigns the paraments above to the two variables face and suit
  face = cardFace;
  suit = cardSuit;
}

inline int card::value() {
  if (face == "Ace")
    return 11;
  if (face == "Jack" or face == "Queen" or face == "King")
    return 10;
  int val = stoi(face);
  return val;
}

inline int card::number() {
  int suitnum;
  int facenum;
  for (int i = 0; i < 4; i++) {
    if (suits[i] == suit) {
      suitnum = i;
      break;
    }
  }
  // cout << "suit= " << suitnum << endl;
  for (int i = 0; i < 13; i++) {

    if (faces[i] == face) {
      facenum = i;
      break;
    }
  }
  // cout << "facenum= "<<facenum << endl;
  return (suitnum * 13) + facenum;
}

// print function defintion
inline string card::print() {
  // return the way the card will be displayed
  string val = face + " of " + suit;
  // cout << val;
  return val;
}
inline int deckOfCards::number() { return currentCard; }
inline int deckOfCards::size() { return deck.size(); }
// assigns the 52 cards to deck
inline deckOfCards::deckOfCards() {

  // initilize deck from the card class to a new array using the word "new"

  // card= new deck[SIZE];

  // current card is equal to zero
  currentCard = 0;
  // create a for loop to literally place each card into the new array
  for (int count = 0; count < SIZE; count++) {
    // deck at postion count will be equal to card, each with a different face
    // and suit
    deck[count] = card(faces[count % 13], suits[count / 13]);
  }
}

// shuffles the deck once all the cards are assigned
inline void deckOfCards::shuffle() {
  // start at current card
  currentCard = 0;
  // create a for loop so all 52 cards will be shuffled
  srand(time(0));
  card temp;
  for (int first = 0; first < SIZE; first++) {
    // create an int called second and set it equal to the random operator
    int second = rand() % SIZE;
    // create an int called temp and set it equal to the deck at the first
    // postiion
    temp = deck[first];
    // swap deck at first and second postion
    deck[first] = deck[second];
    // swap deck and temp
    deck[second] = temp;
  }
}

inline card deckOfCards::dealCard() {
  // if we are out of cards
  if (currentCard > SIZE) {
    // shuffle
    shuffle();
  }
  // if we are not out of cards
  if (currentCard < SIZE) {
    // return deck at that current card and then increment
    return (deck[currentCard++]);
  }
  // return the first card in the deck that we just found
  return (deck[0]);
}

inline void deckOfCards::printDeck() {
  for (int i = 0; i < deck.size(); i++) {
    cout << " card " << i << ": ";
    cout << deck[i].print() << endl;
  }
}