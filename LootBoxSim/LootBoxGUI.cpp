#include "LootBoxGUI.h"


#include <iostream>



LootBoxGUI::LootBoxGUI() :
    window(sf::VideoMode({ 800,600 }), "LootBox Sim"),
    result_text(m_font), p_coins(m_font)
{

    state = Screen::InitialScreen;
    
    if (!m_font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        std::cout << "Failed to load font\n";
    }


    p_coins.setCharacterSize(20);
    //p_coins.setPosition(sf::Vector2f(670, 10));

    result_text.setCharacterSize(28);
    result_text.setPosition(sf::Vector2f(250, 200));



    new_game_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "New Game", window);
    continue_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Continue", window);


    open_box_button = std::make_shared<Button> (sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "Open Box", window);
    shop_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Shop", window);
    inventory_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 190), m_font, "Inventory", window);
    collection_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 280), m_font, "Collection", window);
    upgrades_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 370), m_font, "Upgrades", window);
    save_quit_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 460), m_font, "Save/Quit", window);

    open_button = std::make_shared<Button>(sf::Vector2f(200, 80), sf::Vector2f(300, 500), m_font, "Open Box", window);
    buy_box_button = std::make_shared<Button>(sf::Vector2f(200, 80), sf::Vector2f(10, 10), m_font, "Buy Next Box", window);


    sell_all_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "Sell All", window);
    sell_basic_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Sell Basic", window);
    sell_common_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 190), m_font, "Sell Common", window);
    sell_rare_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 280), m_font, "Sell Rare", window);
    previous_button = std::make_shared<Button>(sf::Vector2f(100, 50), sf::Vector2f(250, 520), m_font, "Prev.", window);
    next_button = std::make_shared<Button>(sf::Vector2f(100, 50), sf::Vector2f(450, 520), m_font, "Next", window);


    upgrade_luck_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "Luck Boost", window);
    upgrade_sell_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Sell Boost", window);
    upgrade_inventory_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 190), m_font, "Inventory boost", window);
    upgrade_open_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 280), m_font, "Multi Open", window);

    back_button = std::make_shared<Button>(sf::Vector2f(75, 60), sf::Vector2f(715, 10), m_font, "Back", window);
}



void LootBoxGUI::newGameLogic()
{
    inv.items.clear();
    inv.coins = 0;

    save.current_save = "";
}

void LootBoxGUI::continueLogic()
{
    std::vector<std::string> save_files = save.getSaveFiles();

    if (save_files.empty())
    {
        std::cout << "No saves found.\n";
        inv.items.clear();
        inv.coins = 0;
        save.current_save = "";
    }
    else
    {
        std::string file = save.chooseSave(save_files);
        save.loadGame(file, inv, collection, box, upgrades, shop);

        std::cout << "\nLoading data...\n";

        save.current_save = file;
    }
}


void LootBoxGUI::openBoxLogic()
{
    std::cout << "\nOPENED BOX\n";


    BoxType& boxtype = shop.boxes[shop.current_box];

    int opens = upgrades.getMultiOpenAmount();
    bool has = false;
    Item reward;

    for (int i = 0; i < opens; i++)
    {
        reward = box.open(boxtype.table, boxtype.name, collection, upgrades);
        has = collection.has(reward.name);
        collection.add(reward.name, reward.rarity);
        inv.addItem(reward);
    }
    
    std::string result;

    result += "Opened " + boxtype.name + "\n\n";
    result += "Rolled: ";
    result += reward.name + " (" + std::to_string(reward.value) + ")";

    if (!has)
    {
        result += " [NEW]";
    }

    result_text.setString(result);
    result_text.setFillColor(RarityUtils::getSFMLColor(reward.rarity));
}


void LootBoxGUI::shopLogic(int choice) 
{
    std::cout << "\nOPENED SHOP\n";

    shop.showShop(inv, upgrades.luck_level);


    if (choice > 0)
    {
        if (choice == 1)
        {
            shop.upgradeBox(inv.coins);
        }
        else
        {
            return;
        }
    }
}

void LootBoxGUI::inventoryLogic(int option)
{
    //inv.showInventory();
    inv.sellItem(upgrades, option);
}

int LootBoxGUI::drawItems()
{
    int start = inv_page * items_per_page;
    int end = std::min(start + items_per_page, static_cast<int>(inv.items.size()));

    float y = 20.f;

    for (int i = start; i < end; i++)
    {
        sf::Text text(m_font);

        text.setString(inv.items[i].name + " (" + std::to_string(inv.items[i].value) + ")");
        text.setCharacterSize(20);
        text.setFillColor(RarityUtils::getSFMLColor(inv.items[i].rarity));
        text.setPosition({ 250.f, y });

        window.draw(text);

        y += 30.f;
    }


    if (start == 0 && end == inv.items.size())
    {
        return 3;
    }
    if (end == inv.items.size())
    {
        return 1;   // last page
    }
    if (start == 0)
    {
        return 2;   // first page
    }

    return 0;
}

void LootBoxGUI::collectionLogic()
{
    collection.show();
}

void LootBoxGUI::upgradesLogic(int choice)
{
    while (true)
    {
        //upgrades.show(inv.coins);

        if (choice == 1)
        {
            upgrades.buyLuck(inv.coins);
            break;
        }
        if (choice == 2)
        {
            upgrades.buySell(inv.coins);
            break;
        }
        if (choice == 3)
        {
            upgrades.buyInventory(inv.coins);
            inv.limit = static_cast<uint64_t>(100 + upgrades.getInventoryBonus());
            break;
        }
        if (choice == 4)
        {
            upgrades.buyMultiOpen(inv.coins);
            break;
        }
    }
}

void LootBoxGUI::saveQuitLogic()
{
    save.saveGame(inv, collection, box, upgrades, shop);

    std::cout << "\nGOODBYE\n";
}


void LootBoxGUI::drawStuff(Screen s_state)
{
    window.clear();

    if (s_state == Screen::InitialScreen)
    {
        new_game_button->draw();
        continue_button->draw();
    }
    else if (s_state == Screen::MainMenuScreen)
    {
        open_box_button->draw();
        shop_button->draw();
        inventory_button->draw();
        collection_button->draw();
        upgrades_button->draw();
        save_quit_button->draw();

        p_coins.setPosition(sf::Vector2f(670, 10));
        p_coins.setString("Coins: " + std::to_string((static_cast<int>(inv.coins))));
        window.draw(p_coins);
    }
    else if (s_state == Screen::OpenScreen)
    {
        open_button->draw();
        back_button->draw();
        window.draw(result_text);
    }
    else if (s_state == Screen::ShopScreen)
    {
        buy_box_button->draw();
        back_button->draw();

        float startY = 300.f;

        BoxType& current = shop.boxes[shop.current_box];

        if (shop.current_box >= shop.boxes.size() - 1)
        {
            sf::Text maxText(m_font);
            maxText.setString("MAX TIER");
            maxText.setPosition({ 300.f, 220.f });
            window.draw(maxText);

            return;
        }
        BoxType& next = shop.boxes[shop.current_box + 1];


        for (size_t i = 0; i < rarities.size(); i++)
        {
            sf::Text rarityText(m_font);
            rarityText.setString(RarityUtils::getName(rarities[i]));
            rarityText.setPosition({ 100.f, startY + i * 40.f });
            rarityText.setFillColor(RarityUtils::getSFMLColor(rarities[i]));

            int currentChanceValue = current.table.getAdjustedChance(rarities[i], upgrades.luck_level, current.name);
            int nextChanceValue = next.table.getAdjustedChance(rarities[i], upgrades.luck_level, next.name);

            sf::Text currentChance(m_font);
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << currentChanceValue;
            currentChance.setString(ss.str() + "%");
            currentChance.setPosition({ 300.f, startY + i * 40.f });

            sf::Text nextChance(m_font);
            std::ostringstream ss1;
            ss1 << std::fixed << std::setprecision(2) << nextChanceValue;
            nextChance.setString(ss1.str() + "%");
            nextChance.setPosition({ 500.f, startY + i * 40.f });

            sf::Text currentBoxText(m_font);
            currentBoxText.setString(current.name);
            currentBoxText.setPosition({ 250.f, 220.f });

            sf::Text nextBoxText(m_font);
            nextBoxText.setString(next.name);
            nextBoxText.setPosition({ 500.f, 220.f });

            p_coins.setPosition(sf::Vector2f(400, 10));
            p_coins.setString("Coins: " + std::to_string((static_cast<int>(inv.coins))));

            window.draw(currentBoxText);
            window.draw(nextBoxText);
            window.draw(rarityText);
            window.draw(currentChance);
            window.draw(nextChance);
            window.draw(p_coins);
        }
    }
    else if (s_state == Screen::InventoryScreen)
    {
        sell_all_button->draw();
        sell_basic_button->draw();
        sell_common_button->draw();
        sell_rare_button->draw();
        back_button->draw();

        int page = drawItems();

        if (page != 3)
        {
            if (page != 1)
            {
                next_button->draw();
            }
            if (page != 2)
            {
                previous_button->draw();
            }
        }
    }
    else if (s_state == Screen::CollectionScreen)
    {
        back_button->draw();
    }
    else if (s_state == Screen::UpgradesScreen)
    {
        upgrade_luck_button->draw();
        upgrade_sell_button->draw();
        upgrade_inventory_button->draw();
        upgrade_open_button->draw();
        back_button->draw();
    }

    window.display();
}


void LootBoxGUI::run()
{
    window.clear();

    if (state == Screen::InitialScreen)
    {
        new_game_button->draw();
        continue_button->draw();
    }

    window.display();

    while (window.isOpen())
    {
        auto event = window.waitEvent();

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else
        {
            bool need_redraw = true;

            if (state == Screen::InitialScreen)
            {
                if (new_game_button->isClicked(event.value()))
                {
                    newGameLogic();
                    state = Screen::MainMenuScreen;
                }
                else if (continue_button->isClicked(event.value()))
                {
                    continueLogic();
                    state = Screen::MainMenuScreen;
                }
            }


            else if (state == Screen::MainMenuScreen)
            {
                if (open_box_button->isClicked(event.value()))
                {
                    state = Screen::OpenScreen;
                    //openBoxLogic();
                }
                else if (shop_button->isClicked(event.value()))
                {
                    state = Screen::ShopScreen;
                    //shopLogic();
                }
                else if (inventory_button->isClicked(event.value()))
                {
                    inv.showInventory();
                    state = Screen::InventoryScreen;
                    //inventoryLogic();
                }
                else if (collection_button->isClicked(event.value()))
                {
                    state = Screen::CollectionScreen;
                    //collectionLogic();
                }
                else if (upgrades_button->isClicked(event.value()))
                {
                    upgrades.show(inv.coins);
                    state = Screen::UpgradesScreen;
                    //upgradesLogic();
                }
                else if (save_quit_button->isClicked(event.value()))
                {
                    saveQuitLogic();
                    window.close();
                }

                else
                {
                    need_redraw = false;
                }
            }


            else if (state == Screen::OpenScreen)
            {
                if (open_button->isClicked(event.value()))
                {
                    openBoxLogic();
                }
                else if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }

                else
                {
                    need_redraw = false;
                }
            }


            else if (state == Screen::ShopScreen)
            {
                if (buy_box_button->isClicked(event.value()))
                {
                    shopLogic(1);
                }
                else if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }

                else
                {
                    need_redraw = false;
                }
            }


            else if (state == Screen::InventoryScreen)
            {
                if (previous_button->isClicked(event.value()))
                {
                    if (inv_page > 0)
                    {
                        inv_page--;
                    }
                }
                else if(next_button->isClicked(event.value()))
                {
                    int max_page = (static_cast<int>(inv.items.size()) - 1) / items_per_page;
                    
                    if (inv_page < max_page)
                    {
                        inv_page++;
                    }
                }
                else if (sell_all_button->isClicked(event.value()))
                {
                    inventoryLogic(1); //sell all
                }
                else if (sell_basic_button->isClicked(event.value()))
                {
                    inventoryLogic(2); //sell basic
                }
                else if (sell_common_button->isClicked(event.value()))
                {
                    inventoryLogic(3); //sell common
                }
                else if (sell_rare_button->isClicked(event.value()))
                {
                    inventoryLogic(4); //sell rare
                }
                else if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }

                else
                {
                    need_redraw = false;
                }
            }


            else if (state == Screen::CollectionScreen)
            {
                if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }

                else
                {
                    need_redraw = false;
                }
            }


            else if (state == Screen::UpgradesScreen)
            {
                if (upgrade_luck_button->isClicked(event.value()))
                {
                    upgradesLogic(1); //luck boost
                }
                else if (upgrade_sell_button->isClicked(event.value()))
                {
                    upgradesLogic(2); //sell boost
                }
                else if (upgrade_inventory_button->isClicked(event.value()))
                {
                    upgradesLogic(3); //inventory size
                }
                else if (upgrade_open_button->isClicked(event.value()))
                {
                    upgradesLogic(4); //multi open
                }
                else if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }

                else
                {
                    need_redraw = false;
                }
            }


            else
            {
                need_redraw = false;    // not an event that does stuff
            }


            if (need_redraw)
            {
                drawStuff(state);
            }
        }
    }
}