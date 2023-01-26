
# Blackjack Game

## Overview
This is a simple implementation of the popular card game Blackjack, written in C++. The game allows for one player to play against the computer (dealer).

## Requirements
- A C++ compiler (e.g. GCC)
- A terminal or command prompt

## How to Play
1. Compile the source code using your C++ compiler (e.g. `g++ main.cpp -o blackjack`)
2. Run the compiled executable file (e.g. `./blackjack`)
3. The game will begin and prompt you to place a bet.
4. The dealer will then deal two cards to the player and two cards to themselves, with one of the dealer's cards being face down.
5. The player can then choose to "hit" (receive another card) or "stand" (keep their current hand).
6. The player can hit as many times as they want, but if their hand exceeds 21, they lose automatically.
7. Once the player stands, the dealer will reveal their face-down card and hit until their hand is at least 17.
8. If the dealer busts (exceeds 21), the player wins. If the player's hand is closer to 21 than the dealer's, the player wins. Otherwise, the dealer wins.

## Game Options
- The player can choose to play again after a game ends, or quit the game.
- The player can choose different difficulty levels for the dealer AI, which affects the dealer's decision-making during gameplay.

## Known Issues
- The game does not currently support splitting or doubling down.
- The game does not currently support betting more than one time.
- The game does not currently support multiple players.

**By: Harman Singh**
