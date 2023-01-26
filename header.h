#ifndef TEST_H 
#define TEST_H

int getRandomNumber(int low, int high);
int CardValue(int card);
int getTopCard(int deck[]);
int getHandValue(const int hand[]);
bool playAnotherHand(char &);
bool userWantsToDraw(char &);
void initializeDeck(int deck[]);
void dumpDeck(int deck[], int size);
void shuffle(int deck[], int size);
void ShowCard(int card);
void ShowCards(const int cards[], int numCards, bool hideFirstCard);
void whoWins(const int pH[], const int dH[]);
void checkBust(const int pH[], const int dH[], char Play);
void blackJack(const int pH[], const int dH[], char Play);
void naturalBlackJack(const int pH[], const int dH[], char play);
void playOneHand();
void scoreBoard(const int pH[], const int dH[]);
void backdoorKenny(const int hand[]);
void checkSoftorHard(int pH[]);
void softorHardAI(int dH[], int pH[]);
void difficulty();
void rules();
void addToHand(int hand[], int cardToHand);
void hitUntilStand(int dH[], int deck[], int pH[]);

#endif