#include "CardSprite.h"

CardSprite::CardSprite(const sf::Font& font)
    : rankText(font, "", 22),
      suitText(font, "", 16),
      faceDown(false)
{
    cardShape.setSize({65.f, 90.f});
    cardShape.setFillColor(sf::Color::White);
    cardShape.setOutlineColor(sf::Color(180, 180, 180));
    cardShape.setOutlineThickness(2.f);
    rankText.setFillColor(sf::Color::Black);
    suitText.setFillColor(sf::Color::Black);
}

void CardSprite::setCard(const Card& card) {
    // --- Rank ---
    std::string rankStr;
    int r = card.getRank();
    if      (r == 14) rankStr = "A";
    else if (r == 13) rankStr = "K";
    else if (r == 12) rankStr = "Q";
    else if (r == 11) rankStr = "J";
    else              rankStr = std::to_string(r);
    rankText.setString(rankStr);
    rankText.setStyle(sf::Text::Bold);

    // --- Suit full word + color ---
    std::string suitStr;
    switch (card.getSuit()) {
        case Suit::Spades:
            suitStr = "Spade";
            suitText.setFillColor(sf::Color::Black);
            rankText.setFillColor(sf::Color::Black);
            break;
        case Suit::Clubs:
            suitStr = "Club";
            suitText.setFillColor(sf::Color(0, 100, 0));   // Dark green
            rankText.setFillColor(sf::Color(0, 100, 0));
            break;
        case Suit::Hearts:
            suitStr = "Heart";
            suitText.setFillColor(sf::Color::Red);
            rankText.setFillColor(sf::Color::Red);
            break;
        case Suit::Diamonds:
            suitStr = "Diam";
            suitText.setFillColor(sf::Color(180, 0, 180)); // Purple
            rankText.setFillColor(sf::Color(180, 0, 180));
            break;
    }
    suitText.setString(suitStr);
}

void CardSprite::setPosition(float x, float y) {
    cardShape.setPosition({x, y});
    rankText.setPosition({x + 8.f, y + 8.f});
    suitText.setPosition({x + 4.f, y + 38.f});
}

void CardSprite::setFaceDown(bool fd) {
    faceDown = fd;
    if (faceDown) {
        cardShape.setFillColor(sf::Color(30, 30, 180));
    } else {
        cardShape.setFillColor(sf::Color::White);
    }
}

void CardSprite::draw(sf::RenderWindow& window) {
    window.draw(cardShape);
    if (!faceDown) {
        window.draw(rankText);
        window.draw(suitText);
    }
}