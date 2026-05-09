#include "Button.h"

#include <iostream>



Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, const std::string& label, sf::RenderWindow& window) : m_text(font), m_window(window)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Blue);

    m_text.setString(label);
    m_text.setCharacterSize(28);

    auto bounds = m_text.getLocalBounds();

    m_text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
        });

    m_text.setPosition(position + size / 2.f);
}

bool Button::isClicked(const sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        auto mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        return m_shape.getGlobalBounds().contains(mouse);
    }
    return false;
}

void Button::draw()
{
    m_window.draw(m_shape);
    m_window.draw(m_text);
}