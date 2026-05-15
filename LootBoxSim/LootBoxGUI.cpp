#include "LootBoxGUI.h"


#include <iostream>



LootBoxGUI::LootBoxGUI() : 
    window(sf::VideoMode({ 800,600 }), "LootBox Sim"),
    result_text(m_font)
{

    state = Screen::InitialScreen;
    
    if (!m_font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        std::cout << "Failed to load font\n";
    }


    //result_text.setFont(m_font);
    result_text.setCharacterSize(28);
    result_text.setPosition(sf::Vector2f(250, 200));
    result_text.setFillColor(sf::Color::White);


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
    bool isnew;
    Item reward;

    for (int i = 0; i < opens; i++)
    {
        reward = box.open(boxtype.table, boxtype.name, collection, upgrades);
        isnew = collection.has(reward.name);
        collection.add(reward.name, reward.rarity);
        inv.addItem(reward);
    }
    
    std::string result;

    result += "Opened " + boxtype.name + "\n\n";
    result += "Rolled: ";
    result += reward.name + " (" + std::to_string(reward.value) + ")";

    if (!isnew)
    {
        result += " [NEW]";
    }

    result_text.setString(result);
}


void LootBoxGUI::shopLogic() 
{
    std::cout << "\nOPENED SHOP\n";

    shop.showShop(inv, upgrades.luck_level);

    int choice;
    std::cin >> choice;

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
    inv.showInventory();
    inv.sellItem(upgrades, option);
}

void LootBoxGUI::collectionLogic()
{
    collection.show();
}

void LootBoxGUI::upgradesLogic()
{
    while (true)
    {
        upgrades.show(inv.coins);

        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            upgrades.buyLuck(inv.coins);
        }
        if (choice == 2)
        {
            upgrades.buySell(inv.coins);
        }
        if (choice == 3)
        {
            upgrades.buyInventory(inv.coins);
            inv.limit = static_cast<uint64_t>(100 + upgrades.getInventoryBonus());
        }
        if (choice == 4)
        {
            upgrades.buyMultiOpen(inv.coins);
        }
        if (choice == 5)
        {
            return;
        }
    }
}

void LootBoxGUI::saveQuitLogic()
{
    save.saveGame(inv, collection, box, upgrades, shop);

    std::cout << "\nGOODBYE\n";
}




void LootBoxGUI::run()
{
    while (window.isOpen())
    {
        window.clear();

        if (state == Screen::InitialScreen)
        {
            new_game_button->draw();
            continue_button->draw();
        }
        else if (state == Screen::MainMenuScreen)
        {
            open_box_button->draw();
            shop_button->draw();
            inventory_button->draw();
            collection_button->draw();
            upgrades_button->draw();
            save_quit_button->draw();
        }
        else if (state == Screen::OpenScreen)
        {
            open_button->draw();
            back_button->draw();
            window.draw(result_text);
        }
        else if (state == Screen::ShopScreen)
        {
            buy_box_button->draw();
            back_button->draw();
        }
        else if (state == Screen::InventoryScreen)
        {
            sell_all_button->draw();
            sell_basic_button->draw();
            sell_common_button->draw();
            sell_rare_button->draw();
            back_button->draw();
        }
        else if (state == Screen::CollectionScreen)
        {
            back_button->draw();
        }
        else if (state == Screen::UpgradesScreen)
        {
            back_button->draw();
        }

        window.display();





        auto event = window.waitEvent();

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else
        {
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
                    state = Screen::InventoryScreen;
                    //inventoryLogic();
                }
                else if (collection_button->isClicked(event.value()))
                {
                    collectionLogic();
                }
                else if (upgrades_button->isClicked(event.value()))
                {
                    upgradesLogic();
                }
                else if (save_quit_button->isClicked(event.value()))
                {
                    saveQuitLogic();
                    window.close();
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
            }
            else if (state == Screen::ShopScreen)
            {
                if (buy_box_button->isClicked(event.value()))
                {
                    shopLogic();
                }
                else if (back_button->isClicked(event.value()))
                {
                    state = Screen::MainMenuScreen;
                }
            }
            else if (state == Screen::InventoryScreen)
            {
                if (sell_all_button->isClicked(event.value()))
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
            }
            //else if (state != Screen::InitialScreen && state != Screen::MainMenuScreen)
            //{
            //    if (back_button->isClicked(event.value()))
            //    {
            //        state = Screen::MainMenuScreen;
            //    }
            //}
        }
    }
}