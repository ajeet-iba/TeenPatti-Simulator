#include <SFML/Graphics.hpp>
#include <string>
#include "Deck.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "CardSprite.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
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

    // Deal 3 cards each
    for (int i = 0; i < 3; ++i) {
        human.addCard(deck.deal());
        ai.addCard(deck.deal());
    }

    // --- Background ---
    sf::RectangleShape background({800.f, 600.f});
    background.setFillColor(sf::Color(80, 20, 20));

    // --- Table ---
    sf::CircleShape table(280.f);
    table.setPointCount(100);
    table.setFillColor(sf::Color(34, 100, 34));
    table.setOutlineColor(sf::Color(139, 90, 43));
    table.setOutlineThickness(8.f);
    table.setOrigin({280.f, 280.f});
    table.setPosition({400.f, 300.f});
    table.setScale({1.4f, 1.0f});

    // --- Title ---
    sf::Text title(font, "Teen Patti Simulator", 28);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition({230.f, 10.f});

    // --- Player 1 (Human - Bottom) ---
    sf::Text p1Name(font, "Ali", 22);
    p1Name.setFillColor(sf::Color::White);
    p1Name.setStyle(sf::Text::Bold);
    p1Name.setPosition({340.f, 490.f});

    sf::Text p1Balance(font, "Balance: $1000", 18);
    p1Balance.setFillColor(sf::Color(255, 215, 0));
    p1Balance.setPosition({300.f, 515.f});

    // --- Player 2 (AI - Top) ---
    sf::Text p2Name(font, "Bot-1", 22);
    p2Name.setFillColor(sf::Color::White);
    p2Name.setStyle(sf::Text::Bold);
    p2Name.setPosition({355.f, 60.f});

    sf::Text p2Balance(font, "Balance: $1000", 18);
    p2Balance.setFillColor(sf::Color(255, 215, 0));
    p2Balance.setPosition({310.f, 85.f});

    // --- Pot ---
    sf::RectangleShape potBox({160.f, 40.f});
    potBox.setFillColor(sf::Color(0, 0, 0, 150));
    potBox.setOutlineColor(sf::Color(255, 215, 0));
    potBox.setOutlineThickness(2.f);
    potBox.setPosition({320.f, 278.f});

    sf::Text potText(font, "POT: $0", 20);
    potText.setFillColor(sf::Color(255, 215, 0));
    potText.setPosition({340.f, 284.f});

    // --- Human Cards (Bottom) ---
    // Fix: store hand in a local reference correctly
    std::vector<Card>& humanHand = human.getHand();
    CardSprite humanCards[3] = {
        CardSprite(font),
        CardSprite(font),
        CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        humanCards[i].setCard(humanHand[i]);
        humanCards[i].setPosition(270.f + i * 80.f, 400.f);
        humanCards[i].setFaceDown(false);  // Human sees own cards
    }

    // --- AI Cards (Top) - Face Down ---
    CardSprite aiCards[3] = {
        CardSprite(font),
        CardSprite(font),
        CardSprite(font)
    };
    for (int i = 0; i < 3; ++i) {
        aiCards[i].setPosition(270.f + i * 80.f, 110.f);
        aiCards[i].setFaceDown(true);  // AI cards hidden
    }

    // --- BET Button ---
    sf::RectangleShape betButton({120.f, 45.f});
    betButton.setFillColor(sf::Color(0, 150, 0));
    betButton.setOutlineColor(sf::Color::White);
    betButton.setOutlineThickness(2.f);
    betButton.setPosition({180.f, 540.f});

    sf::Text betText(font, "BET", 22);
    betText.setFillColor(sf::Color::White);
    betText.setStyle(sf::Text::Bold);
    betText.setPosition({220.f, 550.f});

    // --- FOLD Button ---
    sf::RectangleShape foldButton({120.f, 45.f});
    foldButton.setFillColor(sf::Color(180, 0, 0));
    foldButton.setOutlineColor(sf::Color::White);
    foldButton.setOutlineThickness(2.f);
    foldButton.setPosition({500.f, 540.f});

    sf::Text foldText(font, "FOLD", 22);
    foldText.setFillColor(sf::Color::White);
    foldText.setStyle(sf::Text::Bold);
    foldText.setPosition({537.f, 550.f});

    // --- Game State ---
    int pot = 0;
    bool playerFolded = false;

    // --- Main Loop ---
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Button clicks
            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mouse(
                    static_cast<float>(click->position.x),
                    static_cast<float>(click->position.y)
                );

                // BET clicked
                if (!playerFolded && betButton.getGlobalBounds().contains(mouse)) {
                    pot += 100;
                    potText.setString("POT: $" + std::to_string(pot));
                    betButton.setFillColor(sf::Color(0, 200, 0));
                }

                // FOLD clicked
                if (!playerFolded && foldButton.getGlobalBounds().contains(mouse)) {
                    playerFolded = true;
                    foldText.setString("FOLDED");
                    foldButton.setFillColor(sf::Color(100, 0, 0));
                    p1Name.setFillColor(sf::Color(150, 150, 150));
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