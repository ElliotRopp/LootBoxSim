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


    Screen state;

    sf::RenderWindow window;
    sf::Font m_font;

    std::shared_ptr<Button> new_game_button;
    std::shared_ptr<Button> continue_button;
    std::shared_ptr<Button> select_save_button; // need to make this screen still

    std::shared_ptr<Button> open_box_button;
    std::shared_ptr<Button> shop_button;
    std::shared_ptr<Button> inventory_button;
    std::shared_ptr<Button> collection_button;
    std::shared_ptr<Button> upgrades_button;
    std::shared_ptr<Button> save_quit_button;

    std::shared_ptr<Button> open_button;
    
    std::shared_ptr<Button> buy_box_button;

    std::shared_ptr<Button> sell_all_button;
    std::shared_ptr<Button> sell_basic_button;
    std::shared_ptr<Button> sell_common_button;
    std::shared_ptr<Button> sell_rare_button;


    std::shared_ptr<Button> back_button;

public:
    LootBoxGUI();

    void run();

    void newGameLogic();
    void continueLogic();

    void openBoxLogic();
    void shopLogic();
    void inventoryLogic(int option);
    void collectionLogic();
    void upgradesLogic();
    void saveQuitLogic();
};