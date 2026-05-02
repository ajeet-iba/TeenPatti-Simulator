🃏 Teen Patti Simulator (C++ OOP Project)

A fully object-oriented, console-based Teen Patti (Indian Poker) game simulator built in C++.
The project demonstrates strong OOP principles along with game logic, AI behavior, and hand evaluation.

🎮 Features
🃏 3-card Teen Patti gameplay
👤 Human vs AI player system
🤖 Basic AI betting logic
💰 Betting & pot system
🧠 Hand evaluation system (Trail, Sequence, Pair, etc.)
🔁 Round-based game engine
🎯 Winner determination system
📦 Clean Object-Oriented Design (OOP)

Game Rules:

Each player is dealt 3 cards.

Hand ranking (highest to lowest):

🔥 Trail (Three of a kind)
🌟 Pure Sequence (Same suit consecutive)
🔢 Sequence (Consecutive cards)
🎨 Color (Same suit)
👥 Pair (Two cards same rank)
🧾 High Card

Winner is decided based on the strongest hand.

Project Structure:
TeenPatti/
│
├── Card.h / Card.cpp
├── Deck.h / Deck.cpp
├── Player.h / Player.cpp
├── HumanPlayer.h / HumanPlayer.cpp
├── AIPlayer.h / AIPlayer.cpp
├── GameEngine.h / GameEngine.cpp
├── HandEvaluator.h / HandEvaluator.cpp
├── main.cpp
