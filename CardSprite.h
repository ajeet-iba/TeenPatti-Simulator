#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Card.h"

// Represents a visual card rectangle on screen
class CardSprite {
private:
    sf::RectangleShape cardShape;   // White rectangle
    sf::Text rankText;              // e.g. "A", "K", "7"
    sf::Text suitText;              // e.g. "♠", "♥", "♦", "♣"
    bool faceDown;                  // If true, show card back

public:
    CardSprite(const sf::Font& font);

    // Set which card this sprite shows
    void setCard(const Card& card);

    // Set position on screen
    void setPosition(float x, float y);

    // Show card back (for AI player)
    void setFaceDown(bool faceDown);

    // Draw to window
    void draw(sf::RenderWindow& window);
};