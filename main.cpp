#include <SFML/Graphics.hpp>
#include <string>
#include "Deck.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "CardSprite.h"
#include "HandEvaluator.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode({800, 700}),
        "Teen Patti Simulator"
    );
    window.setFramerateLimit(60);

    // --- Font ---
    sf::Font font;
    if (!font.openFromFile("Arial.ttf")) return -1;

    // --- Lambda to reset the game ---
    // We wrap setup in a function-like block we can call again
    auto setupGame = [&](
        Deck& deck,
        HumanPlayer& human,
        AIPlayer& ai,
        CardSprite humanCards[3],
        CardSprite aiCards[3],
        sf::Text& p1Balance,
        sf::Text& p2Balance,
        sf::Text& potText,
        sf::Text& statusText,
        sf::Text& winnerText,
        sf::RectangleShape& betButton,
        sf::RectangleShape& foldButton,
        sf::Text& betText,
        sf::Text& foldText,
        sf::Text& p1Name,
        int& pot,
        bool& playerActed,
        bool& humanFolded,
        bool& showdown
    ) {
        deck = Deck();
        deck.shuffle();
        human.clearHand();
        ai.clearHand();
        pot = 0;
        playerActed = false;
        humanFolded = false;
        showdown = false;

        for (int i = 0; i < 3; ++i) {
            human.addCard(deck.deal());
            ai.addCard(deck.deal());
        }

        // Reset card sprites
        std::vector<Card>& humanHand = human.getHand();
        std::vector<Card>& aiHand = ai.getHand();
        for (int i = 0; i < 3; ++i) {
            humanCards[i].setCard(humanHand[i]);
            humanCards[i].setFaceDown(false);
            aiCards[i].setCard(aiHand[i]);
            aiCards[i].setFaceDown(true);
        }

        // Reset UI
        p1Balance.setString("Balance: $" + std::to_string(human.getBalance()));
        p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
        potText.setString("POT: $0");
        statusText.setString("Your turn! Bet or Fold.");
        winnerText.setString("");
        betButton.setFillColor(sf::Color(0, 150, 0));
        foldButton.setFillColor(sf::Color(180, 0, 0));
        betText.setString("BET");
        foldText.setString("FOLD");
        p1Name.setFillColor(sf::Color::White);
        p1Balance.setFillColor(sf::Color(255, 215, 0));
    };

    // --- Initial Game Setup ---
    Deck deck;
    deck.shuffle();

    HumanPlayer human("Ali");
    AIPlayer ai("Bot-1");

    for (int i = 0; i < 3; ++i) {
        human.addCard(deck.deal());
        ai.addCard(deck.deal());
    }

    // --- Game State ---
    int pot = 0;
    bool playerActed = false;
    bool humanFolded  = false;
    bool showdown     = false;

    // --- Background ---
    sf::RectangleShape background({800.f, 700.f});
    background.setFillColor(sf::Color(80, 20, 20));

    // --- Table ---
    sf::CircleShape table(240.f);
    table.setPointCount(100);
    table.setFillColor(sf::Color(34, 100, 34));
    table.setOutlineColor(sf::Color(139, 90, 43));
    table.setOutlineThickness(8.f);
    table.setOrigin({240.f, 240.f});
    table.setPosition({400.f, 350.f});
    table.setScale({1.5f, 1.0f});

    // --- Title ---
    sf::Text title(font, "Teen Patti Simulator", 26);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition({240.f, 8.f});

    // --- Player 1 (Human) ---
    sf::Text p1Name(font, "Ali", 20);
    p1Name.setFillColor(sf::Color::White);
    p1Name.setStyle(sf::Text::Bold);
    p1Name.setPosition({360.f, 555.f});

    sf::Text p1Balance(font, "Balance: $1000", 16);
    p1Balance.setFillColor(sf::Color(255, 215, 0));
    p1Balance.setPosition({300.f, 578.f});

    // --- Player 2 (AI) ---
    sf::Text p2Name(font, "Bot-1", 20);
    p2Name.setFillColor(sf::Color::White);
    p2Name.setStyle(sf::Text::Bold);
    p2Name.setPosition({360.f, 45.f});

    sf::Text p2Balance(font, "Balance: $1000", 16);
    p2Balance.setFillColor(sf::Color(255, 215, 0));
    p2Balance.setPosition({310.f, 68.f});

    // --- Pot ---
    sf::RectangleShape potBox({160.f, 40.f});
    potBox.setFillColor(sf::Color(0, 0, 0, 150));
    potBox.setOutlineColor(sf::Color(255, 215, 0));
    potBox.setOutlineThickness(2.f);
    potBox.setPosition({320.f, 310.f});

    sf::Text potText(font, "POT: $0", 20);
    potText.setFillColor(sf::Color(255, 215, 0));
    potText.setPosition({340.f, 316.f});

    // --- Status Message ---
    sf::Text statusText(font, "Your turn! Bet or Fold.", 16);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition({250.f, 365.f});

    // --- Winner Announcement ---
    sf::Text winnerText(font, "", 26);
    winnerText.setFillColor(sf::Color::Yellow);
    winnerText.setStyle(sf::Text::Bold);
    winnerText.setPosition({200.f, 280.f});

    // --- Human Cards ---
    std::vector<Card>& humanHand = human.getHand();
    CardSprite humanCards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        humanCards[i].setCard(humanHand[i]);
        humanCards[i].setPosition(270.f + i * 80.f, 455.f);
        humanCards[i].setFaceDown(false);
    }

    // --- AI Cards ---
    std::vector<Card>& aiHand = ai.getHand();
    CardSprite aiCards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        aiCards[i].setCard(aiHand[i]);
        aiCards[i].setPosition(270.f + i * 80.f, 110.f);
        aiCards[i].setFaceDown(true);
    }

    // --- BET Button ---
    sf::RectangleShape betButton({120.f, 45.f});
    betButton.setFillColor(sf::Color(0, 150, 0));
    betButton.setOutlineColor(sf::Color::White);
    betButton.setOutlineThickness(2.f);
    betButton.setPosition({150.f, 630.f});

    sf::Text betText(font, "BET", 22);
    betText.setFillColor(sf::Color::White);
    betText.setStyle(sf::Text::Bold);
    betText.setPosition({190.f, 640.f});

    // --- FOLD Button ---
    sf::RectangleShape foldButton({120.f, 45.f});
    foldButton.setFillColor(sf::Color(180, 0, 0));
    foldButton.setOutlineColor(sf::Color::White);
    foldButton.setOutlineThickness(2.f);
    foldButton.setPosition({530.f, 630.f});

    sf::Text foldText(font, "FOLD", 22);
    foldText.setFillColor(sf::Color::White);
    foldText.setStyle(sf::Text::Bold);
    foldText.setPosition({562.f, 640.f});

    // --- Play Again Button (hidden until showdown) ---
    sf::RectangleShape playAgainButton({180.f, 45.f});
    playAgainButton.setFillColor(sf::Color(0, 100, 180));
    playAgainButton.setOutlineColor(sf::Color::White);
    playAgainButton.setOutlineThickness(2.f);
    playAgainButton.setPosition({310.f, 630.f});

    sf::Text playAgainText(font, "PLAY AGAIN", 20);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setStyle(sf::Text::Bold);
    playAgainText.setPosition({330.f, 642.f});

    // --- Main Loop ---
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mouse(
                    static_cast<float>(click->position.x),
                    static_cast<float>(click->position.y)
                );

                // --- Human's turn ---
                if (!playerActed) {

                    // BET clicked
                    if (betButton.getGlobalBounds().contains(mouse)) {
                        human.bet(100);
                        pot += 100;
                        potText.setString("POT: $" + std::to_string(pot));
                        p1Balance.setString("Balance: $" + std::to_string(human.getBalance()));

                        // AI bets too
                        ai.bet(100);
                        pot += 100;
                        potText.setString("POT: $" + std::to_string(pot));
                        p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));

                        playerActed = true;
                        showdown = true;

                        // --- Evaluate winner ---
                        int humanRank = HandEvaluator::evaluate(human.getHand());
                        int aiRank    = HandEvaluator::evaluate(ai.getHand());

                        // Flip AI cards face up
                        for (int i = 0; i < 3; ++i) {
                            aiCards[i].setFaceDown(false);
                        }

                        // Announce winner
                        if (humanRank > aiRank) {
                            human.addBalance(pot);
                            p1Balance.setString("Balance: $" + std::to_string(human.getBalance()));
                            winnerText.setString("Ali WINS $" + std::to_string(pot) + "!");
                            winnerText.setFillColor(sf::Color::Green);
                        } else if (aiRank > humanRank) {
                            ai.addBalance(pot);
                            p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
                            winnerText.setString("Bot-1 WINS $" + std::to_string(pot) + "!");
                            winnerText.setFillColor(sf::Color::Red);
                        } else {
                            // Tie — split pot
                            human.addBalance(pot / 2);
                            ai.addBalance(pot / 2);
                            p1Balance.setString("Balance: $" + std::to_string(human.getBalance()));
                            p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
                            winnerText.setString("It's a TIE! Pot split!");
                            winnerText.setFillColor(sf::Color::Yellow);
                        }

                        pot = 0;
                        potText.setString("POT: $0");
                        statusText.setString(HandEvaluator::handName(humanRank) + 
                                           " vs " + 
                                           HandEvaluator::handName(aiRank));

                        // Disable bet/fold buttons
                        betButton.setFillColor(sf::Color(0, 60, 0));
                        foldButton.setFillColor(sf::Color(60, 0, 0));
                    }

                    // FOLD clicked
                    if (foldButton.getGlobalBounds().contains(mouse)) {
                        human.fold();
                        humanFolded = true;
                        playerActed = true;
                        showdown = true;

                        // Flip AI cards
                        for (int i = 0; i < 3; ++i) {
                            aiCards[i].setFaceDown(false);
                        }

                        ai.addBalance(pot);
                        p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
                        winnerText.setString("You folded! Bot-1 WINS!");
                        winnerText.setFillColor(sf::Color::Red);
                        statusText.setString("Better luck next time!");
                        p1Name.setFillColor(sf::Color(150, 150, 150));
                        p1Balance.setFillColor(sf::Color(150, 150, 150));
                        foldText.setString("FOLDED");
                        betButton.setFillColor(sf::Color(0, 60, 0));
                        foldButton.setFillColor(sf::Color(60, 0, 0));
                        pot = 0;
                        potText.setString("POT: $0");
                    }
                }

                // --- Play Again clicked ---
                if (showdown && playAgainButton.getGlobalBounds().contains(mouse)) {
                    setupGame(
                        deck, human, ai,
                        humanCards, aiCards,
                        p1Balance, p2Balance,
                        potText, statusText, winnerText,
                        betButton, foldButton,
                        betText, foldText,
                        p1Name, pot,
                        playerActed, humanFolded, showdown
                    );
                }
            }
        }

        // --- Draw ---
        window.clear(sf::Color(80, 20, 20));
        window.draw(background);
        window.draw(table);
        window.draw(title);
        window.draw(potBox);
        window.draw(potText);
        window.draw(statusText);
        window.draw(winnerText);
        window.draw(p1Name);
        window.draw(p1Balance);
        window.draw(p2Name);
        window.draw(p2Balance);

        for (int i = 0; i < 3; ++i) {
            humanCards[i].draw(window);
            aiCards[i].draw(window);
        }

        // Show BET/FOLD only before showdown
        // Show PLAY AGAIN only after showdown
        if (!showdown) {
            window.draw(betButton);
            window.draw(betText);
            window.draw(foldButton);
            window.draw(foldText);
        } else {
            window.draw(playAgainButton);
            window.draw(playAgainText);
        }

        window.display();
    }

    return 0;
}