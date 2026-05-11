#include "LootBoxGUI.h"


#include <iostream>



LootBoxGUI::LootBoxGUI() : 
    window(sf::VideoMode({ 800,600 }), "LootBox Sim")
{
    
    if (!m_font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        std::cout << "Failed to load font\n";
    }

    new_game_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "New Game", window);
    continue_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Continue", window);

    open_box_button = std::make_shared<Button> (sf::Vector2f(150, 60), sf::Vector2f(10, 10), m_font, "Open Box", window);
    shop_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 100), m_font, "Shop", window);
    inventory_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 190), m_font, "Inventory", window);
    collection_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 280), m_font, "Collection", window);
    upgrades_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 370), m_font, "Upgrades", window);
    save_quit_button = std::make_shared<Button>(sf::Vector2f(150, 60), sf::Vector2f(10, 460), m_font, "Save/Quit", window);
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

    for (int i = 0; i < opens; i++)
    {
        Item reward = box.open(boxtype.table, boxtype.name, collection, upgrades);

        collection.add(reward.name, reward.rarity);
        inv.addItem(reward);
    }
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

void LootBoxGUI::inventoryLogic()
{
    inv.sellItem(upgrades);
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
    Screen state = Screen::InitialScreen;


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
                    openBoxLogic();
                }
                else if (shop_button->isClicked(event.value()))
                {
                    shopLogic();
                }
                else if (inventory_button->isClicked(event.value()))
                {
                    inventoryLogic();
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
                }
            }
        }
    }
}