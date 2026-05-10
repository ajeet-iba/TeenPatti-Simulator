#include <SFML/Graphics.hpp>
#include <string>
#include "Deck.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "CardSprite.h"
#include "HandEvaluator.h"

enum class Screen { START, GAME };

int main() {
    sf::RenderWindow window(
        sf::VideoMode({900, 750}),
        "Teen Patti Simulator"
    );
    window.setFramerateLimit(60);

    // --- Font ---
    sf::Font font;
    if (!font.openFromFile("Arial.ttf")) return -1;

    // --- Screen state ---
    Screen currentScreen = Screen::START;
    std::string playerName = "";

    // =====================
    // START SCREEN ELEMENTS
    // =====================

    sf::RectangleShape startBg({900.f, 750.f});
    startBg.setFillColor(sf::Color(20, 20, 20));

    sf::Text startTitle(font, "Teen Patti", 72);
    startTitle.setFillColor(sf::Color(255, 215, 0));
    startTitle.setStyle(sf::Text::Bold);
    startTitle.setPosition({230.f, 80.f});

    sf::Text startSubtitle(font, "Simulator", 36);
    startSubtitle.setFillColor(sf::Color::White);
    startSubtitle.setPosition({345.f, 165.f});

    sf::RectangleShape divider({500.f, 3.f});
    divider.setFillColor(sf::Color(255, 215, 0));
    divider.setPosition({200.f, 230.f});

    sf::Text nameLabel(font, "Enter Your Name:", 22);
    nameLabel.setFillColor(sf::Color(200, 200, 200));
    nameLabel.setPosition({295.f, 280.f});

    sf::RectangleShape nameBox({300.f, 45.f});
    nameBox.setFillColor(sf::Color(40, 40, 40));
    nameBox.setOutlineColor(sf::Color(255, 215, 0));
    nameBox.setOutlineThickness(2.f);
    nameBox.setPosition({300.f, 320.f});

    sf::Text nameInput(font, "", 22);
    nameInput.setFillColor(sf::Color::White);
    nameInput.setPosition({310.f, 328.f});

    sf::RectangleShape cursor({2.f, 28.f});
    cursor.setFillColor(sf::Color::White);
    sf::Clock cursorClock;
    bool cursorVisible = true;

    sf::RectangleShape playButton({200.f, 55.f});
    playButton.setFillColor(sf::Color(0, 150, 0));
    playButton.setOutlineColor(sf::Color::White);
    playButton.setOutlineThickness(2.f);
    playButton.setPosition({350.f, 420.f});

    sf::Text playText(font, "PLAY", 28);
    playText.setFillColor(sf::Color::White);
    playText.setStyle(sf::Text::Bold);
    playText.setPosition({415.f, 432.f});

    sf::Text errorText(font, "", 18);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition({300.f, 495.f});

    sf::Text bootInfo(font, "3 Players  |  Boot: $50 each  |  Bet: $100", 16);
    bootInfo.setFillColor(sf::Color(150, 150, 150));
    bootInfo.setPosition({250.f, 545.f});

    sf::Text credits(font, "OOP Course Project", 16);
    credits.setFillColor(sf::Color(80, 80, 80));
    credits.setPosition({360.f, 710.f});

    // =====================
    // GAME SCREEN ELEMENTS
    // =====================

    // --- Players ---
    // Human at bottom, Bot-1 at top-left, Bot-2 at top-right
    HumanPlayer* human = nullptr;
    AIPlayer* ai1      = new AIPlayer("Bot-1");
    AIPlayer* ai2      = new AIPlayer("Bot-2");

    const int BOOT = 50;
    int pot        = 0;
    bool playerActed = false;
    bool showdown    = false;
    bool humanFolded = false;
    bool ai1Folded   = false;
    bool ai2Folded   = false;
    Deck deck;

    // --- Background ---
    sf::RectangleShape background({900.f, 750.f});
    background.setFillColor(sf::Color(80, 20, 20));

    // --- Table ---
    sf::CircleShape table(260.f);
    table.setPointCount(100);
    table.setFillColor(sf::Color(34, 100, 34));
    table.setOutlineColor(sf::Color(139, 90, 43));
    table.setOutlineThickness(8.f);
    table.setOrigin({260.f, 260.f});
    table.setPosition({450.f, 370.f});
    table.setScale({1.5f, 1.0f});

    // --- Title ---
    sf::Text title(font, "Teen Patti Simulator", 26);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition({290.f, 8.f});

    // --- Human (bottom center) ---
    sf::Text p1Name(font, "", 20);
    p1Name.setFillColor(sf::Color::White);
    p1Name.setStyle(sf::Text::Bold);
    p1Name.setPosition({400.f, 590.f});

    sf::Text p1Balance(font, "Balance: $1000", 15);
    p1Balance.setFillColor(sf::Color(255, 215, 0));
    p1Balance.setPosition({365.f, 613.f});

    // --- Bot-1 (top left) ---
    sf::Text p2Name(font, "Bot-1", 20);
    p2Name.setFillColor(sf::Color::White);
    p2Name.setStyle(sf::Text::Bold);
    p2Name.setPosition({130.f, 50.f});

    sf::Text p2Balance(font, "Balance: $1000", 15);
    p2Balance.setFillColor(sf::Color(255, 215, 0));
    p2Balance.setPosition({95.f, 73.f});

    // --- Bot-2 (top right) ---
    sf::Text p3Name(font, "Bot-2", 20);
    p3Name.setFillColor(sf::Color::White);
    p3Name.setStyle(sf::Text::Bold);
    p3Name.setPosition({660.f, 50.f});

    sf::Text p3Balance(font, "Balance: $1000", 15);
    p3Balance.setFillColor(sf::Color(255, 215, 0));
    p3Balance.setPosition({625.f, 73.f});

    // --- Pot ---
    sf::RectangleShape potBox({180.f, 40.f});
    potBox.setFillColor(sf::Color(0, 0, 0, 150));
    potBox.setOutlineColor(sf::Color(255, 215, 0));
    potBox.setOutlineThickness(2.f);
    potBox.setPosition({360.f, 340.f});

    sf::Text potText(font, "POT: $0", 20);
    potText.setFillColor(sf::Color(255, 215, 0));
    potText.setPosition({380.f, 346.f});

    // --- Status ---
    sf::Text statusText(font, "", 15);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition({260.f, 395.f});

    // --- Hand name ---
    sf::Text handNameText(font, "", 15);
    handNameText.setFillColor(sf::Color(180, 255, 180));
    handNameText.setPosition({260.f, 460.f});

    // --- Winner text ---
    sf::Text winnerText(font, "", 26);
    winnerText.setFillColor(sf::Color::Yellow);
    winnerText.setStyle(sf::Text::Bold);
    winnerText.setPosition({200.f, 295.f});

    // --- Game over text ---
    sf::Text gameOverText(font, "", 24);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition({180.f, 260.f});

    // --- Human cards (bottom center) ---
    CardSprite humanCards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i)
        humanCards[i].setPosition(320.f + i * 75.f, 495.f);

    // --- Bot-1 cards (top left) ---
    CardSprite ai1Cards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        ai1Cards[i].setPosition(60.f + i * 75.f, 105.f);
        ai1Cards[i].setFaceDown(true);
    }

    // --- Bot-2 cards (top right) ---
    CardSprite ai2Cards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        ai2Cards[i].setPosition(590.f + i * 75.f, 105.f);
        ai2Cards[i].setFaceDown(true);
    }

    // --- BET Button ---
    sf::RectangleShape betButton({130.f, 45.f});
    betButton.setFillColor(sf::Color(0, 150, 0));
    betButton.setOutlineColor(sf::Color::White);
    betButton.setOutlineThickness(2.f);
    betButton.setPosition({180.f, 680.f});

    sf::Text betText(font, "BET $100", 20);
    betText.setFillColor(sf::Color::White);
    betText.setStyle(sf::Text::Bold);
    betText.setPosition({188.f, 692.f});

    // --- FOLD Button ---
    sf::RectangleShape foldButton({130.f, 45.f});
    foldButton.setFillColor(sf::Color(180, 0, 0));
    foldButton.setOutlineColor(sf::Color::White);
    foldButton.setOutlineThickness(2.f);
    foldButton.setPosition({590.f, 680.f});

    sf::Text foldText(font, "FOLD", 22);
    foldText.setFillColor(sf::Color::White);
    foldText.setStyle(sf::Text::Bold);
    foldText.setPosition({627.f, 690.f});

    // --- Play Again Button ---
    sf::RectangleShape playAgainButton({170.f, 45.f});
    playAgainButton.setFillColor(sf::Color(0, 100, 180));
    playAgainButton.setOutlineColor(sf::Color::White);
    playAgainButton.setOutlineThickness(2.f);
    playAgainButton.setPosition({260.f, 680.f});

    sf::Text playAgainText(font, "PLAY AGAIN", 20);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setStyle(sf::Text::Bold);
    playAgainText.setPosition({270.f, 692.f});

    // --- Main Menu Button ---
    sf::RectangleShape menuButton({170.f, 45.f});
    menuButton.setFillColor(sf::Color(120, 60, 0));
    menuButton.setOutlineColor(sf::Color::White);
    menuButton.setOutlineThickness(2.f);
    menuButton.setPosition({470.f, 680.f});

    sf::Text menuText(font, "MAIN MENU", 20);
    menuText.setFillColor(sf::Color::White);
    menuText.setStyle(sf::Text::Bold);
    menuText.setPosition({485.f, 692.f});

    // --- Helper: start a fresh round ---
    auto startRound = [&]() {
        deck = Deck();
        deck.shuffle();
        human->clearHand();
        ai1->clearHand();
        ai2->clearHand();

        // Boot amount
        human->bet(BOOT);
        ai1->bet(BOOT);
        ai2->bet(BOOT);
        pot = BOOT * 3;

        playerActed = false;
        showdown    = false;
        humanFolded = false;
        ai1Folded   = false;
        ai2Folded   = false;

        // Deal 3 cards each
        for (int i = 0; i < 3; ++i) {
            human->addCard(deck.deal());
            ai1->addCard(deck.deal());
            ai2->addCard(deck.deal());
        }

        // Update card sprites
        std::vector<Card>& hh  = human->getHand();
        std::vector<Card>& ah1 = ai1->getHand();
        std::vector<Card>& ah2 = ai2->getHand();

        for (int i = 0; i < 3; ++i) {
            humanCards[i].setCard(hh[i]);
            humanCards[i].setFaceDown(false);
            ai1Cards[i].setCard(ah1[i]);
            ai1Cards[i].setFaceDown(true);
            ai2Cards[i].setCard(ah2[i]);
            ai2Cards[i].setFaceDown(true);
        }

        // Update UI
        p1Balance.setString("Balance: $" + std::to_string(human->getBalance()));
        p2Balance.setString("Balance: $" + std::to_string(ai1->getBalance()));
        p3Balance.setString("Balance: $" + std::to_string(ai2->getBalance()));
        potText.setString("POT: $" + std::to_string(pot));
        statusText.setString("Boot paid! Your turn: Bet or Fold.");

        int hr = HandEvaluator::evaluate(human->getHand());
        handNameText.setString("Your hand: " + HandEvaluator::handName(hr));

        winnerText.setString("");
        gameOverText.setString("");
        betButton.setFillColor(sf::Color(0, 150, 0));
        foldButton.setFillColor(sf::Color(180, 0, 0));
        betText.setString("BET $100");
        foldText.setString("FOLD");
        p1Name.setFillColor(sf::Color::White);
        p1Balance.setFillColor(sf::Color(255, 215, 0));
        p2Name.setFillColor(sf::Color::White);
        p2Balance.setFillColor(sf::Color(255, 215, 0));
        p3Name.setFillColor(sf::Color::White);
        p3Balance.setFillColor(sf::Color(255, 215, 0));
    };

    // ==========
    // MAIN LOOP
    // ==========
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // ====================
            // START SCREEN EVENTS
            // ====================
            if (currentScreen == Screen::START) {

                if (const auto* text = event->getIf<sf::Event::TextEntered>()) {
                    if (text->unicode == 8) {
                        if (!playerName.empty()) {
                            playerName.pop_back();
                            nameInput.setString(playerName);
                        }
                    } else if (playerName.size() < 12 &&
                               text->unicode >= 32 &&
                               text->unicode < 128) {
                        playerName += static_cast<char>(text->unicode);
                        nameInput.setString(playerName);
                    }
                }

                if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                    if (key->code == sf::Keyboard::Key::Enter) {
                        if (!playerName.empty()) {
                            delete human;
                            human = new HumanPlayer(playerName);
                            p1Name.setString(playerName);
                            startRound();
                            currentScreen = Screen::GAME;
                        } else {
                            errorText.setString("Please enter your name!");
                        }
                    }
                }

                if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mouse(
                        static_cast<float>(click->position.x),
                        static_cast<float>(click->position.y)
                    );
                    if (playButton.getGlobalBounds().contains(mouse)) {
                        if (!playerName.empty()) {
                            delete human;
                            human = new HumanPlayer(playerName);
                            p1Name.setString(playerName);
                            startRound();
                            currentScreen = Screen::GAME;
                        } else {
                            errorText.setString("Please enter your name!");
                        }
                    }
                }
            }

            // ==================
            // GAME SCREEN EVENTS
            // ==================
            if (currentScreen == Screen::GAME) {
                if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mouse(
                        static_cast<float>(click->position.x),
                        static_cast<float>(click->position.y)
                    );

                    if (!playerActed) {

                        // BET clicked
                        if (betButton.getGlobalBounds().contains(mouse)) {
                            human->bet(100);
                            pot += 100;

                            // AI 1 decision — simple: always bet
                            ai1->bet(100);
                            pot += 100;

                            // AI 2 decision — simple: always bet
                            ai2->bet(100);
                            pot += 100;

                            potText.setString("POT: $" + std::to_string(pot));
                            p1Balance.setString("Balance: $" + std::to_string(human->getBalance()));
                            p2Balance.setString("Balance: $" + std::to_string(ai1->getBalance()));
                            p3Balance.setString("Balance: $" + std::to_string(ai2->getBalance()));

                            playerActed = true;
                            showdown    = true;

                            // Flip all AI cards
                            for (int i = 0; i < 3; ++i) {
                                ai1Cards[i].setFaceDown(false);
                                ai2Cards[i].setFaceDown(false);
                            }

                            // Evaluate all hands
                            int humanRank = HandEvaluator::evaluate(human->getHand());
                            int ai1Rank   = HandEvaluator::evaluate(ai1->getHand());
                            int ai2Rank   = HandEvaluator::evaluate(ai2->getHand());

                            // Find winner
                            int bestRank = humanRank;
                            std::string winnerName = playerName;
                            bool humanWins = true;

                            if (ai1Rank > bestRank) {
                                bestRank   = ai1Rank;
                                winnerName = "Bot-1";
                                humanWins  = false;
                            }
                            if (ai2Rank > bestRank) {
                                bestRank   = ai2Rank;
                                winnerName = "Bot-2";
                                humanWins  = false;
                            }

                            // Award winner
                            if (winnerName == playerName) {
                                human->addBalance(pot);
                                winnerText.setString(playerName + " WINS $" + std::to_string(pot) + "!");
                                winnerText.setFillColor(sf::Color::Green);
                            } else if (winnerName == "Bot-1") {
                                ai1->addBalance(pot);
                                winnerText.setString("Bot-1 WINS $" + std::to_string(pot) + "!");
                                winnerText.setFillColor(sf::Color::Red);
                            } else {
                                ai2->addBalance(pot);
                                winnerText.setString("Bot-2 WINS $" + std::to_string(pot) + "!");
                                winnerText.setFillColor(sf::Color::Red);
                            }

                            pot = 0;
                            potText.setString("POT: $0");
                            p1Balance.setString("Balance: $" + std::to_string(human->getBalance()));
                            p2Balance.setString("Balance: $" + std::to_string(ai1->getBalance()));
                            p3Balance.setString("Balance: $" + std::to_string(ai2->getBalance()));
                            statusText.setString(
                                playerName + ": " + HandEvaluator::handName(humanRank) +
                                " | Bot-1: " + HandEvaluator::handName(ai1Rank) +
                                " | Bot-2: " + HandEvaluator::handName(ai2Rank)
                            );
                            handNameText.setString("");
                            betButton.setFillColor(sf::Color(0, 60, 0));
                            foldButton.setFillColor(sf::Color(60, 0, 0));

                            // Game over check
                            if (human->getBalance() <= 0) {
                                gameOverText.setString("GAME OVER! You ran out of money!");
                                gameOverText.setFillColor(sf::Color::Red);
                            } else if (ai1->getBalance() <= 0 && ai2->getBalance() <= 0) {
                                gameOverText.setString("YOU WIN THE GAME! Both bots are broke!");
                                gameOverText.setFillColor(sf::Color::Green);
                            }
                        }

                        // FOLD clicked
                        if (foldButton.getGlobalBounds().contains(mouse)) {
                            human->fold();
                            humanFolded = true;
                            playerActed = true;
                            showdown    = true;

                            // Flip all AI cards
                            for (int i = 0; i < 3; ++i) {
                                ai1Cards[i].setFaceDown(false);
                                ai2Cards[i].setFaceDown(false);
                            }

                            // AI vs AI — find winner between bots
                            int ai1Rank = HandEvaluator::evaluate(ai1->getHand());
                            int ai2Rank = HandEvaluator::evaluate(ai2->getHand());

                            if (ai1Rank >= ai2Rank) {
                                ai1->addBalance(pot);
                                winnerText.setString("You folded! Bot-1 WINS $" + std::to_string(pot) + "!");
                            } else {
                                ai2->addBalance(pot);
                                winnerText.setString("You folded! Bot-2 WINS $" + std::to_string(pot) + "!");
                            }
                            winnerText.setFillColor(sf::Color::Red);

                            pot = 0;
                            potText.setString("POT: $0");
                            p2Balance.setString("Balance: $" + std::to_string(ai1->getBalance()));
                            p3Balance.setString("Balance: $" + std::to_string(ai2->getBalance()));
                            statusText.setString("You folded! Better luck next time!");
                            handNameText.setString("");
                            p1Name.setFillColor(sf::Color(150, 150, 150));
                            p1Balance.setFillColor(sf::Color(150, 150, 150));
                            foldText.setString("FOLDED");
                            betButton.setFillColor(sf::Color(0, 60, 0));
                            foldButton.setFillColor(sf::Color(60, 0, 0));

                            if (human->getBalance() <= 0) {
                                gameOverText.setString("GAME OVER! You ran out of money!");
                                gameOverText.setFillColor(sf::Color::Red);
                            }
                        }
                    }

                    // PLAY AGAIN
                    if (showdown && playAgainButton.getGlobalBounds().contains(mouse)) {
                        if (human->getBalance() > BOOT &&
                            ai1->getBalance() > BOOT &&
                            ai2->getBalance() > BOOT) {
                            startRound();
                        } else {
                            gameOverText.setString("Not enough balance to continue!");
                            gameOverText.setFillColor(sf::Color::Red);
                        }
                    }

                    // MAIN MENU
                    if (showdown && menuButton.getGlobalBounds().contains(mouse)) {
                        delete human;
                        human = nullptr;
                        delete ai1;
                        delete ai2;
                        ai1 = new AIPlayer("Bot-1");
                        ai2 = new AIPlayer("Bot-2");
                        playerName = "";
                        nameInput.setString("");
                        errorText.setString("");
                        currentScreen = Screen::START;
                    }
                }
            }
        }

        // Cursor blink
        if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
            cursorVisible = !cursorVisible;
            cursorClock.restart();
        }
        cursor.setPosition({
            312.f + nameInput.getLocalBounds().size.x + 2.f,
            327.f
        });

        // =======
        // DRAW
        // =======
        window.clear();

        if (currentScreen == Screen::START) {
            window.draw(startBg);
            window.draw(startTitle);
            window.draw(startSubtitle);
            window.draw(divider);
            window.draw(nameLabel);
            window.draw(nameBox);
            window.draw(nameInput);
            if (cursorVisible) window.draw(cursor);
            window.draw(playButton);
            window.draw(playText);
            window.draw(errorText);
            window.draw(bootInfo);
            window.draw(credits);
        }

        if (currentScreen == Screen::GAME) {
            window.draw(background);
            window.draw(table);
            window.draw(title);
            window.draw(potBox);
            window.draw(potText);
            window.draw(statusText);
            window.draw(handNameText);
            window.draw(winnerText);
            window.draw(gameOverText);
            window.draw(p1Name);
            window.draw(p1Balance);
            window.draw(p2Name);
            window.draw(p2Balance);
            window.draw(p3Name);
            window.draw(p3Balance);

            for (int i = 0; i < 3; ++i) {
                humanCards[i].draw(window);
                ai1Cards[i].draw(window);
                ai2Cards[i].draw(window);
            }

            if (!showdown) {
                window.draw(betButton);
                window.draw(betText);
                window.draw(foldButton);
                window.draw(foldText);
            } else {
                window.draw(playAgainButton);
                window.draw(playAgainText);
                window.draw(menuButton);
                window.draw(menuText);
            }
        }

        window.display();
    }

    delete human;
    delete ai1;
    delete ai2;
    return 0;
}