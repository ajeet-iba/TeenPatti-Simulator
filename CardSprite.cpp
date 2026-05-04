#include "CardSprite.h"

CardSprite::CardSprite(const sf::Font& font)
    : rankText(font, "", 20),
      suitText(font, "", 18),
      faceDown(false)
{
    // White card rectangle
    cardShape.setSize({60.f, 90.f});
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

    // --- Suit symbol + color ---
    std::string suitStr;
    switch (card.getSuit()) {
        case Suit::Spades:   suitStr = "S"; suitText.setFillColor(sf::Color::Black); rankText.setFillColor(sf::Color::Black); break;
        case Suit::Clubs:    suitStr = "C"; suitText.setFillColor(sf::Color::Black); rankText.setFillColor(sf::Color::Black); break;
        case Suit::Hearts:   suitStr = "H"; suitText.setFillColor(sf::Color::Red);   rankText.setFillColor(sf::Color::Red);   break;
        case Suit::Diamonds: suitStr = "D"; suitText.setFillColor(sf::Color::Red);   rankText.setFillColor(sf::Color::Red);   break;
    }
    suitText.setString(suitStr);
}

void CardSprite::setPosition(float x, float y) {
    cardShape.setPosition({x, y});
    rankText.setPosition({x + 5.f, y + 5.f});
    suitText.setPosition({x + 5.f, y + 30.f});
}

void CardSprite::setFaceDown(bool fd) {
    faceDown = fd;
    if (faceDown) {
        cardShape.setFillColor(sf::Color(30, 30, 180));  // Blue back
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