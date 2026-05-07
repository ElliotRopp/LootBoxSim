#include <iostream>
#include <algorithm>

#include "Inventory.h"
#include "RarityUtils.h"
#include "Upgrades.h"


void Inventory::addItem(Item item)
{
    if (items.size() < limit)
    {
        items.push_back(item);
    }
    else
    {
        std::cout << "Inventory full!\n";
    }
}


void Inventory::showInventory()
{
    std::cout << "\n=== INVENTORY ===\n";

    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ": " << RarityUtils::getColor(items[i].rarity)
            << RarityUtils::getName(items[i].rarity) << ' '
            << items[i].name
            << " (" << items[i].value << ")\033[0m\n";
    }
    std::cout << "Coins: " << coins << '\n'
        << "Items: " << items.size() << '\n';
}


void Inventory::sellItem(Upgrades& upgrade)
{
    while (true)
    {
        if (items.empty())
        {
            std::cout << "Invetory is empty!\n:";
            return;
        }

        std::vector<uint64_t> indices;
        int choice;

        showInventory();

        std::cout << "\nSell all Basics (-2)\n";
        std::cout << "Sell all Commons (-3)\n";
        std::cout << "Sell all Rares (-4)\n";
        std::cout << "Sell all items (-5)\n";
        std::cout << "Back to menu (-6)\n";
        std::cout << "Enter the indexes of the items you want to sell with a space separating each one (-1 to finish): ";

        while (std::cin >> choice)
        {
            if (choice != -1)
            {
                break;
            }
            if (choice == -6)
            {
                return;
            }
            if (choice == -2)
            {
                double total = 0;

                std::erase_if(items, [&total](Item item)
                {
                    bool isBasic = item.rarity == Rarity::Basic;
                    if (isBasic) total += item.value;
                    return isBasic;
                });

                std::cout << "Sold all Basics for " << total * upgrade.getSellBonus() << " coins\n";
                coins += floor(total * upgrade.getSellBonus());

                //return;
            }
            if (choice == -3)
            {
                double total = 0;

                std::erase_if(items, [&total](Item item)
                {
                    bool isCommon = item.rarity == Rarity::Common;
                    if (isCommon) total += item.value;
                    return isCommon;
                });

                std::cout << "\nSold all Commons for " << total * upgrade.getSellBonus() << " coins\n";
                coins += floor(total * upgrade.getSellBonus());
                //return;
            }
            if (choice == -4)
            {
                double total = 0;

                std::erase_if(items, [&total](Item item)
                {
                    bool isRare = item.rarity == Rarity::Rare;
                    if (isRare) total += item.value;
                    return isRare;
                });

                std::cout << "\nSold all Rares for " << total * upgrade.getSellBonus() << " coins\n";
                coins += floor(total * upgrade.getSellBonus());
                //return;
            }
            if (choice == -5)
            {
                double total = 0;

                std::cout << '\n';


                //while (!items.empty())
                for(auto& item : items)
                {
                    
                    std::cout << "Sold: " << RarityUtils::getColor(item.rarity) << item.name << "\033[0m\n";

                    total += item.value;
                }

                items.clear();

                std::cout << "\n+" << total * upgrade.getSellBonus() << " coins\n";

                coins += floor(total * upgrade.getSellBonus());
                //return;
            }

            if (choice > static_cast<int>(items.size()))
            {
                std::cout << "Item doesn't exist!\n";
            }
            else
            {
                indices.push_back(static_cast<uint64_t>(choice - 1));
            }
        }


        if (indices.empty())
        {
            std::cout << "No items selected.\n";
            return;
        }

        std::sort(indices.rbegin(), indices.rend());

        double total = 0;

        std::cout << '\n';

        for (auto i : indices)
        {
            if (i < items.size())
            {
                std::cout << "Sold: " << RarityUtils::getColor(items[i].rarity) << items[i].name << "\033[0m\n";

                total += items[i].value;
                items.erase(items.begin() + i);
            }
        }


        std::cout << "\n+" << total * upgrade.getSellBonus() << " coins\n";

        coins += floor(total * upgrade.getSellBonus());
    } 
}