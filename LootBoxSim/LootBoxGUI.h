#pragma once

#include "Button.h"
#include "LootBox.h"
#include "Shop.h"
#include "Upgrades.h"
#include "Collection.h"
#include "SaveSystem.h"
#include "Screen.h"

#include <SFML/Graphics.hpp>
#include <memory>

class LootBoxGUI
{
private:

    Inventory inv;
    LootBox box;
    Shop shop;
    SaveSystem save;
    Collection collection;
    Upgrades upgrades;


    sf::RenderWindow window;
    sf::Font m_font;

    std::shared_ptr<Button> new_game_button;
    std::shared_ptr<Button> continue_button;

    std::shared_ptr<Button> open_box_button;
    std::shared_ptr<Button> shop_button;
    std::shared_ptr<Button> inventory_button;
    std::shared_ptr<Button> collection_button;
    std::shared_ptr<Button> upgrades_button;
    std::shared_ptr<Button> save_quit_button;

public:
    LootBoxGUI();

    void run();

    void newGameLogic();
    void continueLogic();

    void openBoxLogic();
    void shopLogic();
    void inventoryLogic();
    void collectionLogic();
    void upgradesLogic();
    void saveQuitLogic();
};