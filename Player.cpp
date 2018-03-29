// Klayton Kowalski

#include "Player.h"

Player::Player() : Character(sf::Vector2f(0.0f, 0.0f), 0, 24, 16, 32, "Player")
{
    m_TextureCoords = sf::Vector2f(0.0f, 0.0f);
    m_Universal = true;
}

Player::~Player() {}
