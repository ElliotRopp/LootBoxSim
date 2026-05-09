#include "LootBoxGUI.h"

#include <iostream>



LootBoxGUI::LootBoxGUI() : 
    window(sf::VideoMode({ 800,600 }), "LootBox Sim")
{
    
    if (!m_font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        std::cout << "Failed to load font\n";
    }

    open_box_button = std::make_shared<Button> (sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "Open Box", window);
    shop_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Shop", window);


}













void LootBoxGUI::openBoxLogic()
{
    std::cout << "\nOPENED BOX\n";


}

void LootBoxGUI::shopLogic()
{
    std::cout << "\nOPENED SHOP\n";
}





void LootBoxGUI::run()
{
    while (window.isOpen())
    {
        window.clear();

        open_box_button->draw();
        shop_button->draw();

        window.display();

        auto event = window.waitEvent();

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        else
        {
            if (open_box_button->isClicked(event.value()))
            {
                openBoxLogic();
            }
            else if (shop_button->isClicked(event.value()))
            {
                shopLogic();
            }
        }

    }


}