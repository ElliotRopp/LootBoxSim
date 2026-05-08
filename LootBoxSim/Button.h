#pragma once


#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::RenderWindow& m_window;

public:
    Button() {};
    void InitButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, const std::string& label, sf::RenderWindow& window);
    bool isClicked(const sf::Event& event);
    void draw();
};