#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

// function declaration

#include "header.h"

// global variables
int topcard = 0;
float win = 1.0;
int level;

// rules

void rules() {
  cout << "**********************************************" << endl;
  cout << "**********WELCOME TO BLACKJACK GAME***********" << endl;
  cout << "~~Rules~~" << endl;
  cout << "1. Aces can either be 1 or 11 points." << endl;
  cout << "2. Dealer wins ties unless player has a blackjack." << endl;
  cout << "----------------------------------------------" << endl;
  cout << "~~Winnings~~" << endl;
  cout << "Your score beats dealer's score - 100% increase in bet." << endl;
  cout << "Dealer's score beats your score = 100% decrease in bet." << endl;
  cout << "Blackjack - 150% increase in bet." << endl;
  cout << "Natural Blackjack - 50% increase in bet." << endl;
  cout << "Backdoor Kenny - 25% increase in bet." << endl;
  cout << "Push (Tie) - " << endl;
  cout << "a) 1:1 payout if in your favour." << endl;
  cout << "   (100%) increase of your initial bet)." << endl;
  cout << "b) 0:1 payout if in dealer's favour." << endl;
  cout << "   (No loss, no Gain)" << endl;
  cout << "------------------------------------------------------" << endl;
  cout << "---------------------Difficulty-----------------------" << endl;
  cout << "1. Beginner - Dealer stands at a soft 17 and has no AI." << endl;
  cout << "2. Expert - Dealer hits at a soft 17 and has no AI." << endl;
  cout << "*****************************************************" << endl;
}

// setting difficulty
void difficulty() {
  cout << "Difficulty level : Beginner (1) , Expert (2)" << endl;
  cout << "Enter a difficulty level, ie, 1 or 2" << endl;
  cin >> level;
  while (!(level == 1 || 2)) {
    cout << "Enter a difficulty level, ie, 1 or 2" << endl;
    cin >> level;
    if (level == 1 || 2) {
      break;
    }
  }
}

//main game running function
void playOneHand() {
  char Play = 'N'; // Declare local variable
  do {
    char Draw = 'H'; // Declare local variable
    int deck[52];    // Declare, initialize and shuffle the deck.
    initializeDeck(deck);
    shuffle(deck, 51);
    int pH[10] = {0};
    int dH[10] = {0};
    addToHand(pH, getTopCard(deck)); // Deal first round
    addToHand(dH, getTopCard(deck));
    addToHand(pH, getTopCard(deck));
    addToHand(dH, getTopCard(deck));
    cout << "*************************************" << endl;
    cout << "\n" << endl;
    cout << "The Dealer shuffled and dealt you each your cards. ";
    cout << "\n" << endl;
    naturalBlackJack(pH, dH, 'y');
    blackJack(pH, dH, 'Y');
    cout << "Your hand:" << endl;
    ShowCards(pH, 10, false);
    cout << "\n\nDealer's hand:" << endl;
    ShowCards(dH, 10, true);
    checkSoftorHard(pH);
    while (userWantsToDraw(Draw)) {
      addToHand(pH, getTopCard(deck));
      cout << "The Dealer dealt you another card.\n" << endl;
      cout << "Your hand:" << endl;
      ShowCards(pH, 10, false);
      checkSoftorHard(pH);
      checkBust(pH, dH, 'y');
      blackJack(pH, dH, 'Y');
    }
    hitUntilStand(dH, deck, pH); // Dealer hits until at a soft 17
    cout << endl;
    checkBust(pH, dH, 'Y'); // Check to see if anyone lost
    blackJack(pH, dH, 'Y'); // Check to see if anyone won
    whoWins(pH, dH);        // Compare scores and determine winner
    cout << endl;
    cout << "Winnings multiplier:" << win << endl;
  } while (playAnotherHand(Play));
}

void initializeDeck(int deck[]) {
  int Rank = 101;
  int i = 0;
  for (i = 0; i <= 13; i++) { // Hearts
    deck[i] = Rank++;
  }
  for (i = 13; i <= 26; i++) { // Diamonds
    deck[i] = Rank++ + 100 - 14;
  }
  for (i = 26; i <= 39; i++) { // Clubs
    deck[i] = Rank++ + 200 - 28;
  }
  for (i = 39; i <= 51; i++) { // Spades
    deck[i] = Rank++ + 300 - 42;
  }
}

void shuffle(int deck[], int size) {
  for (int i = 0; i < 500; i++) { // Loop through deck 
    int T1 = 0;
    int R1 = getRandomNumber(0, size);
    int R2 = getRandomNumber(0, size);
    T1 = deck[R1];       // Clone first card for safe keeping
    deck[R1] = deck[R2]; // Replace first card with a new card
    deck[R2] = T1;       // Replace the new card with the old card clone
  }
}

int getTopCard(int deck[]) {
  for (int i = 0; i < 51; i++) { // Find a card that isn't empty
    if (deck[i] != 0) {
      topcard = deck[i]; // Clone card for safe keeping
      deck[i] = 0;       // Replace first card with the empty card valu
      return topcard;    // Return the clone of the card
    }
  }
}

void addToHand(int hand[], int cardToAdd) {
  for (int i = 0; i < 9; i++) { // Loop through the hand
    if (hand[i] == 0) {         // If there is an empty card spot
      hand[i] = cardToAdd;      // Replace it with the card to add
      break;                    // Only do this once by breaking the loop
    }
  }
}

void naturalBlackJack(const int pH[], const int dH[], char Play) {
  int playerScore = getHandValue(pH);
  int dealerScore = getHandValue(dH);
  // If Player has blackjack and Dealer doesnt
  if ((playerScore == 21) && (dealerScore != 21)) {
    scoreBoard(pH, dH);
    cout << "\n";
    cout << "Natural Blackjack! You win a 3:2 payout.";
    win = win + 1.5;
    backdoorKenny(pH);
    playAnotherHand(Play);
  }
}

void blackJack(const int pH[], const int dH[], char Play) {
  int playerScore = getHandValue(pH);
  int dealerScore = getHandValue(dH);
  // If Player has blackjack but Dealer doesn't.
  if ((playerScore == 21) && (dealerScore != 21)) {
    cout << "\n\n";
    scoreBoard(pH, dH);
    cout << "\n";
    cout << "Blackjack! You win a 3:2 payout." << endl;
    win = win + 1.5;
    cout << "\n";
    cout << "Winnings multiplier: " << win << endl;
    backdoorKenny(pH);
    playAnotherHand(Play);
  } // If both Player and Dealer have blackjack.
  else if ((playerScore == 21) && (dealerScore == 21)) {
    scoreBoard(pH, dH);
    cout << "\n";
    cout << "Dealer & you got Blakjack. Push in your favor at 1:1 ratio"
         << endl;
    win++;
    cout << "\n";
    cout << "Winnings multiplier: " << win << endl;
    playAnotherHand(Play);
  }
}

void ShowCards(const int deck[], int numCards, bool hideFirstCard) {
  if (hideFirstCard) { // Hide dealer's first card if true.
    cout << "**";
  } else { // Show dealer's first card if false.
    ShowCard(deck[0]);
    cout << " ";
  }
  for (int i = 1; i < numCards; i++) {
    // Display all cards in deck or hand i.e. rant or suit graphic
    if (deck[i] != 0) { // Show cards
      ShowCard(deck[i]);
      cout << " ";
    } else { // Show nothing for non cards (ie. 0)
      cout << "";
    }
  }
}

void checkSoftorHard(int pH[]) {
  for (int i = 0; i < 9; i++) { // check cards in hand
    int checkAce = CardValue(pH[i]);
    int softorHard;
    // If card in hand is an Ace prompt Player for input
    if (checkAce == 1 || checkAce == 11) {
      cout << "\n";
      cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11): ";
      cin >> softorHard;
      if (softorHard == 1) { // If Player chooses 1
        if (checkAce == 11)
          pH[i] = pH[i] + 13;
      } else if (softorHard == 11) { // If Player chooses 1
        if (checkAce == 1) {
          pH[i] = pH[i] - 13;
        }
      } else if (softorHard != 1 || softorHard != 11) {
        // Clear input error flags & removes everything currently in input
        // buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Display error message and restart the function
        cout << "\nPlease enter the number 1 or 11." << endl;
        checkSoftorHard(pH);
      }
    }
  }
}

bool userWantsToDraw(char &Draw) { // Prompt if like to enter a new time.
  cout << endl << "\nWould you like to hit or stand? (H/S) ";
  cin >> Draw;
  cout << "\n";
  if (Draw == 'h' || Draw =='H') { // If yes, return true and start the loop to draw another card

    return (true);
  } else { // If don't, skip the loop.
    return (false);
  }
}

void checkBust(const int pH[], const int dH[], char Play) {
  int playerScore = getHandValue(pH);
  int dealerScore = getHandValue(dH);
  if (playerScore > 21) { // Check if Player busts.
    cout << "You bust with " << getHandValue(pH) << " points." << endl;
    cout << "\n" << endl;
    win--;
    cout << "Winnings multiplier: " << win << endl;
    playAnotherHand(Play);
  } else if (dealerScore > 21) { // Check if Dealer busts
    scoreBoard(pH, dH);
    cout << "\n" << endl;
    cout << "The Dealer went bust. You Win!" << endl;
    cout << "\n" << endl;
    win++;
    cout << "Winnings multiplier: " << win << endl;
    playAnotherHand(Play);
  }
}

void hitUntilStand(int dH[], int deck[], int pH[]) {
  for (int i = 0; i < 9; i++) {  // Loop through Dealer's hand
    if (getHandValue(dH) < 17) { // If Dealer must hit
      // If Player chose Beginner level dealer stands at soft 17
      if (level == 1) { //...add a card to the hand
        addToHand(dH, getTopCard(deck));
      }
      // If Player chose Expert level dealer stands at Hard 17
      else if (level == 2) { //...add a card to the hand
        addToHand(dH, getTopCard(deck));
        // Ensure Aces are handled intelligently to beat Player
        softorHardAI(dH, pH);
      }
    }
    // Display how many cards Dealer hit if Dealer has 17 or more points
    else {
      if (i == 0) { // Dealer didn't hit to get to 17
        cout << "The Dealer stands." << endl;
        break;
      } else if (i == 1) { // Dealer hit once to get to 17
        cout << "The Dealer hit a card and stands." << endl;
        break;
      } else { // Dealer hit more than once to get to 17
        cout << "The Dealer hit " << i << " cards & stands." << endl;
        break;
      }
    }
    // Run dealer AI again if player chose to play Expert //This is called again
    // for the sake of redundancy.
    if (level == 1)
      ;
    else if (level == 2) {
      softorHardAI(dH, pH);
    }
  }
}

int getHandValue(const int hand[]) {
  int addCardValues = 0;
  for (int i = 0; i < 9; i++) { // add up the card values
    addCardValues = addCardValues + CardValue(hand[i]);
  }
  return addCardValues; // sum of the card values as the hand value
}

int CardValue(int card) {
  int cardVal;
  // Get the card's background 10s value and assign the card a point value
  switch (card % 100) {
  case 1:
    cardVal = 11;
    break;
  case 11:
  case 12:
  case 13:
    cardVal = 10;
    break;
  case 14:
    cardVal = 1;
    break;
  // For non-face cards, just use their backround 10s value as point value.
  default:
    cardVal = (card % 100);
  }
  return cardVal;
}

void scoreBoard(const int pH[], const int dH[]) {
  cout << "Player hand: "; // Display Player's cards/hand value
  ShowCards(pH, 10, false);
  cout << " (" << getHandValue(pH) << "pts)." << endl;
  cout << "V.S." << endl;
  cout << "Dealer hand: "; // Display Dealer's cards/hand value ShowCards (dH,
                           // 10, false);
  cout << "(" << getHandValue(dH) << "pts)." << endl;
}

void backdoorKenny(const int hand[]) {
  // If index 0 is a 10 and index 1 is an ace
  if ((CardValue(hand[0]) % 100 == 10) && (CardValue(hand[1]) % 100 == 11)) {
    // I did not use 1 as an argument because 11 is the default
    // value and this happens before the user can choose.

    cout << "\n\n";
    cout << "You pulled a Backdoor Kenny!\n" << endl;
    cout << "Win an additional 1:4 payout\n" << endl;
    win = win + .25;
    cout << "Winnings multiplier: " << win << endl;
  }
}

void ShowCard(int card) {
  if (card == 0) {
    // Show nothing for non cards (ie.0)
    cout << "";
  } else { // Define Ranks.
    switch (card % 100) {
    case 1:
      cout << "A";
      break;
    case 11:
      cout << "J";
      break;
    case 12:
      cout << "K";
      break;
    case 13:
      cout << "Q";
      break;
    case 14:
      // 14 is a value created in checkSoftorHard
      cout << "A";
      break;
    default: // For non-face cards, use their 10s value as rank.
      cout << card % 100;
    }
  }
  if (card == 0) { // Show nothing for non cards (ie.0)
    cout << "";
  } else {                                // Define Suits.
    if ((card >= 101) && (card <= 114)) { // Hearts
      cout << static_cast<char>(3);
    } else if ((card >= 201) && (card <= 214)) { // Diamonds
      cout << static_cast<char>(4);
    } else if ((card >= 301) && (card <= 314)) { // Clubs
      cout << static_cast<char>(5);
    } else if ((card >= 401) && (card <= 414)) { // Spades
      cout << static_cast<char>(6); //changing data type
    }
  }
}

void dumpDeck(int deck[], int size) {
  for (int i = 0; i < size; i++) {
    cout << i + 1 << ".) " << deck[i] << endl;
  }
}

int getRandomNumber(int low, int high) {
  static bool firstTime = true;
  int randNum;
  if (firstTime) { // if 1st time called, seed random number generator
    srand(static_cast<unsigned int>(time(NULL)));
  }
  firstTime = false;
  // generate random number between given low and high values (inclusive)
  randNum = rand() % (high - low + 1) + low;
  return randNum;
}

void softorHardAI(int dH[], int pH[]) {
  for (int i = 0; i < 9; i++) { // check cards in hand
    if (CardValue(dH[i]) == 1 || CardValue(dH[i] == 11)) {
      if (CardValue(dH[i] == 11)) { // if the ace is worth 11 points , change it
                                    // to 1 point if that will beat the player.
        if (getHandValue(dH) - CardValue(dH[i]) + 1 > getHandValue(pH)) {
          if (getHandValue(dH) - CardValue(dH[i]) + 1 <
              22) { // to make sure it not busts
            dH[i] = dH[i] + 13;
          }
        } else if (getHandValue(dH) > 21) {
          dH[i] = dH[i] + 13;
        }
      } else { // Else Ace is worth 1 point.
        // Change it to 11 points if that will beat player...
        if (getHandValue(dH) - CardValue(dH[i]) + 11 > getHandValue(pH)) {
          if (getHandValue(dH) - CardValue(dH[i]) + 11 < 22) { // and not bust.
            dH[i] = dH[i] - 13;
          }
        }
      }
    }
  }
}

void whoWins(const int pH[], const int dH[]) {
  int playerScore = getHandValue(pH);
  int dealerScore = getHandValue(dH);
  scoreBoard(pH, dH); // Display the scoreboard
  // win
  if (((playerScore < 22) && (playerScore > dealerScore)) ||
      ((playerScore < 22) && (dealerScore > 21))) {
    cout << "\n";
    cout << "You win!" << endl;
    win++;                               // compute new winnings multiplier
  }                                      // If you don't win, you lose or tie.
  else if (playerScore == dealerScore) { // Tie
    cout << "\n";
    cout << "Push in the Dealer's favor. 0:1 payout." << endl;
  } else { // lose
    cout << "\n";
    cout << "You lose." << endl;
    win--; // compute new winnings multiplier
  }
}

bool playAnotherHand(char &Play) { // Prompt if want to play another hand
  cout << endl << "\nWould you like to play another hand? (Y/N)";
  cin >> Play;
  cout << "\n" << endl;
  if (Play == 'y' || Play == 'Y') {
    playOneHand(); // GO to main game logic function to restart|
    return true;
  } else { // If don't, exit the program.
    if (win > 0) {
      cout << "\nYou're quite good at this.\n";
    } else if (win < 0) {
      cout << "\nThe dealer seems to be a tough opponent for you.(laughing noise)\n";
    }
    cout << "\nThanks for playing!";
    exit(1);
  }
}

int main() {
  rules();
  difficulty();
  playOneHand();
}
