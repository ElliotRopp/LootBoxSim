#pragma once

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>

class LootBoxGUI
{
private:
    sf::RenderWindow window;
    sf::Font m_font;

    std::shared_ptr<Button> open_box_button;
    std::shared_ptr<Button> shop_button;
    std::shared_ptr<Button> inventory_button;
    std::shared_ptr<Button> collection_button;
    std::shared_ptr<Button> upgrades_button;
    std::shared_ptr<Button> save_quit_button;

public:
    LootBoxGUI();

    void run();

    void openBoxLogic();
    void shopLogic();
    void inventoryLogic();
    void collectionLogic();
    void upgradesLogic();
    void saveQuitLogic();
};