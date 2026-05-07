#include <SFML/Graphics.hpp>
#include <string>
#include "Deck.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "CardSprite.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode({800, 700}),
        "Teen Patti Simulator"
    );
    window.setFramerateLimit(60);

    // --- Font ---
    sf::Font font;
    if (!font.openFromFile("Arial.ttf")) return -1;

    // --- Game Setup ---
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
    bool playerActed = false;   // Has human taken their turn?
    bool aiActed = false;       // Has AI taken its turn?
    bool humanFolded = false;
    std::string statusMessage = "Your turn! Bet or Fold.";

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

    // --- Player 1 (Human - Bottom) ---
    sf::Text p1Name(font, "Ali", 20);
    p1Name.setFillColor(sf::Color::White);
    p1Name.setStyle(sf::Text::Bold);
    p1Name.setPosition({360.f, 555.f});

    sf::Text p1Balance(font, "Balance: $" + std::to_string(human.getBalance()), 16);
    p1Balance.setFillColor(sf::Color(255, 215, 0));
    p1Balance.setPosition({300.f, 578.f});

    // --- Player 2 (AI - Top) ---
    sf::Text p2Name(font, "Bot-1", 20);
    p2Name.setFillColor(sf::Color::White);
    p2Name.setStyle(sf::Text::Bold);
    p2Name.setPosition({360.f, 45.f});

    sf::Text p2Balance(font, "Balance: $" + std::to_string(ai.getBalance()), 16);
    p2Balance.setFillColor(sf::Color(255, 215, 0));
    p2Balance.setPosition({310.f, 68.f});

    // --- Pot ---
    sf::RectangleShape potBox({160.f, 40.f});
    potBox.setFillColor(sf::Color(0, 0, 0, 150));
    potBox.setOutlineColor(sf::Color(255, 215, 0));
    potBox.setOutlineThickness(2.f);
    potBox.setPosition({320.f, 330.f});

    sf::Text potText(font, "POT: $0", 20);
    potText.setFillColor(sf::Color(255, 215, 0));
    potText.setPosition({340.f, 336.f});

    // --- Status Message (center of table) ---
    sf::Text statusText(font, statusMessage, 16);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition({250.f, 390.f});

    // --- Human Cards (Bottom) ---
    std::vector<Card>& humanHand = human.getHand();
    CardSprite humanCards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        humanCards[i].setCard(humanHand[i]);
        humanCards[i].setPosition(270.f + i * 80.f, 455.f);
        humanCards[i].setFaceDown(false);
    }

    // --- AI Cards (Top) - Face Down ---
    CardSprite aiCards[3] = {
        CardSprite(font), CardSprite(font), CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
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

    // --- Main Loop ---
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Only listen for clicks if human hasn't acted yet
            if (!playerActed) {
                if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mouse(
                        static_cast<float>(click->position.x),
                        static_cast<float>(click->position.y)
                    );

                    // --- BET clicked ---
                    if (betButton.getGlobalBounds().contains(mouse)) {
                        // Deduct from human balance
                        human.bet(100);
                        pot += 100;

                        // Update displays
                        potText.setString("POT: $" + std::to_string(pot));
                        p1Balance.setString("Balance: $" + std::to_string(human.getBalance()));

                        // Disable buttons visually
                        betButton.setFillColor(sf::Color(0, 80, 0));
                        foldButton.setFillColor(sf::Color(80, 0, 0));
                        playerActed = true;

                        // AI responds — always bets
                        ai.bet(100);
                        pot += 100;
                        potText.setString("POT: $" + std::to_string(pot));
                        p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
                        aiActed = true;

                        statusText.setString("Bot-1 also bet $100! Waiting for showdown...");
                    }

                    // --- FOLD clicked ---
                    if (foldButton.getGlobalBounds().contains(mouse)) {
                        human.fold();
                        humanFolded = true;
                        playerActed = true;

                        // Grey out human side
                        p1Name.setFillColor(sf::Color(150, 150, 150));
                        p1Balance.setFillColor(sf::Color(150, 150, 150));
                        foldText.setString("FOLDED");

                        // Disable buttons
                        betButton.setFillColor(sf::Color(0, 80, 0));
                        foldButton.setFillColor(sf::Color(80, 0, 0));

                        // AI wins automatically
                        ai.addBalance(pot);
                        p2Balance.setString("Balance: $" + std::to_string(ai.getBalance()));
                        statusText.setString("You folded! Bot-1 wins the pot!");
                        aiActed = true;
                    }
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
        window.draw(p1Name);
        window.draw(p1Balance);
        window.draw(p2Name);
        window.draw(p2Balance);

        for (int i = 0; i < 3; ++i) {
            humanCards[i].draw(window);
            aiCards[i].draw(window);
        }

        window.draw(betButton);
        window.draw(betText);
        window.draw(foldButton);
        window.draw(foldText);
        window.display();
    }

    return 0;
}