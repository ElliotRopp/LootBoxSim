#pragma once

#include "Button.h"
#include <SFML/Graphics.hpp>


class LootBoxGUI
{
private:
    sf::RenderWindow window;

    Button open_box_button;
    Button shop_button;
    Button inventory_button;
    Button collection_button;
    Button upgrades_button;
    Button save_quit_button;

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