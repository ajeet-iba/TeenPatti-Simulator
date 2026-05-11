# Teen Patti Simulator 🃏

A graphical Teen Patti (3-Card Poker) game built in C++ using SFML, developed as a university OOP course project.

---

## 🎮 Features
- Full graphical interface using SFML 3
- 3 players — You vs Bot-1 vs Bot-2
- Real Teen Patti hand rankings
- Boot amount system ($50 per player per round)
- BET and FOLD buttons with live balance updates
- AI cards hidden (face down) until showdown
- Winner announced with hand comparison
- Play Again and Main Menu buttons
- Start screen with custom name entry
- Game over detection when balance runs out

---

### Compile
```bash
g++ -std=c++17 main.cpp Card.cpp Deck.cpp Player.cpp HumanPlayer.cpp AIPlayer.cpp GameEngine.cpp HandEvaluator.cpp CardSprite.cpp -o teen_patti.exe -I"C:/msys64/ucrt64/include" -L"C:/msys64/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system
```

### Run
```bash
.\teen_patti.exe
```

---

---

## 🛠️ How to Build and Run

### Requirements
- Windows with MSYS2 installed
- GCC 15.x (via MSYS2 UCRT64)
- SFML 3 (installed via pacman)

### Install SFML (one time only)
Open UCRT64 terminal and run:
```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### Copy required DLL files
Copy these from `C:\msys64\ucrt64\bin\` into your project folder:
libsfml-graphics-3.dll
libsfml-window-3.dll
libsfml-system-3.dll

## 🎯 How to Play
1. Launch the game and type your name on the start screen
2. Click **PLAY** to start
3. Each player pays a **$50 boot** into the pot automatically
4. Your 3 cards are dealt face up — Bot cards are hidden
5. Choose your action:
   - **BET $100** — Add $100 to the pot. Bots also bet. Best hand wins!
   - **FOLD** — Give up your hand. Bots play against each other.
6. After showdown, AI cards are revealed and the winner is announced
7. Click **PLAY AGAIN** to start a new round with the same balances
8. Click **MAIN MENU** to go back to the start screen

---

## 🐛 Known Limitations
- Tie-breaking between equal hand ranks uses first-found logic
- AI always bets (no bluffing or folding logic yet)
- No sound effects

---

## 🃏 Hand Rankings (Highest to Lowest)
| Rank | Hand: Description 
| 6 | Trail (Three of a Kind): Three cards of the same rank
| 5 | Pure Sequence: Three consecutive cards of the same suit
| 4 | Sequence: Three consecutive cards, different suits 
| 3 | Color (Flush): Three cards of the same suit 
| 2 | Pair: Two cards of the same rank 
| 1 | High Card: None of the above 
Winner is decided based on the strongest hand.

---

## 🗂️ Project Structure
TeenPatti/
|-- main.cpp            - Game loop, SFML rendering, screen management
|-- GameEngine.h/.cpp   - Core game logic, round management, winner resolution
|-- Player.h/.cpp       - Abstract base class for all players
|-- HumanPlayer.h/.cpp  - Human player (GUI-controlled)
|-- AIPlayer.h/.cpp     - AI player (auto-bets each round)
|-- Card.h/.cpp         - Card data structure (rank + suit)
|-- Deck.h/.cpp         - 52-card deck with shuffle and deal
|-- CardSprite.h/.cpp   - SFML visual representation of a card
|-- HandEvaluator.h/.cpp - Evaluates and names Teen Patti hands
|-- Arial.ttf           - Font file used for all text rendering



