#pragma once

#include "Button.h"
#include "LootBox.h"
#include "Shop.h"
#include "Upgrades.h"
#include "Collection.h"
#include "SaveSystem.h"
#include "Screen.h"
#include "RarityUtils.h"
#include "Rarity.h"

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


    std::vector<Rarity> rarities =
    {
        Rarity::Basic,
        Rarity::Common,
        Rarity::Rare,
        Rarity::Epic,
        Rarity::Legendary,
        Rarity::Mythic,
        Rarity::Celestial
    };


    Screen state;

    sf::RenderWindow window;
    sf::Font m_font;

    sf::Text p_coins;

    sf::Text result_text;



    std::shared_ptr<Button> new_game_button;
    std::shared_ptr<Button> continue_button;
    //std::shared_ptr<Button> select_save_button;

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
    std::shared_ptr<Button> previous_button;
    std::shared_ptr<Button> next_button;

    std::shared_ptr<Button> upgrade_luck_button;
    std::shared_ptr<Button> upgrade_sell_button;
    std::shared_ptr<Button> upgrade_inventory_button;
    std::shared_ptr<Button> upgrade_open_button;


    std::shared_ptr<Button> back_button;


    const int items_per_page = 15;
    int inv_page = 0;

public:
    LootBoxGUI();

    void run();

    void drawStuff(Screen s_state);

    void newGameLogic();
    void continueLogic();

    int drawItems();

    void openBoxLogic();
    void shopLogic(int choice);
    void inventoryLogic(int option);
    void collectionLogic();
    void upgradesLogic(int choice);
    void saveQuitLogic();
};