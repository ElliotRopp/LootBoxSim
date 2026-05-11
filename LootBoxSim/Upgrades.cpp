#include "Upgrades.h"

#include <iostream>
#include <cmath>


int Upgrades::getLuckBonus()
{
	return luck_level * 2;
}

double Upgrades::getSellBonus()
{
	return 1.0 + (sell_level * 0.2);
}

int Upgrades::getInventoryBonus()
{
	return inventory_level * 2;
}

int Upgrades::getMultiOpenAmount()
{
    if (multi_open_level == 0) return 1;
    if (multi_open_level == 1) return 2;
    if (multi_open_level == 2) return 3;
    if (multi_open_level == 3) return 5;

    return 1;
}

void Upgrades::show(double coins)
{
    std::cout << "\n=================================\n";
    std::cout << "             UPGRADES\n";
    std::cout << "=================================\n";

    std::cout << "Coins: " << coins << "\n\n";

    int luckCost = static_cast<int>(150 * pow(1.6, luck_level));
    int sellCost = static_cast<int>(200 * pow(1.6, sell_level));
    int invCost = static_cast<int>(250 * pow(1.6, inventory_level));

    int currentLuck = getLuckBonus();
    int nextLuck = (luck_level + 1) * 2;

    int currentInv = getInventoryBonus();
    int nextInv = (inventory_level + 1) * 2;

    double currentSell = (getSellBonus() - 1.0) * 100;
    int nextSell = (sell_level + 1) * 20;

    std::cout << "1. Luck Upgrade\n";
    std::cout << "   Level: " << luck_level << "\n";
    std::cout << "   Effect: +" << currentLuck << "% -> +" << nextLuck << "% better rarity odds\n";

    if (luck_level < 10)
    {
        std::cout << "   Cost: " << luckCost << " coins\n\n";
    }
    else
    {
        std::cout << "   MAX LEVEL\n";
    }

    std::cout << "2. Sell Boost\n";
    std::cout << "   Level: " << sell_level << "\n";
    std::cout << "   Effect: +" << currentSell << "% -> +" << nextSell << "% sell value\n";

    if (sell_level < 10)
    {
        std::cout << "   Cost: " << sellCost << " coins\n\n";
    }
    else
    {
        std::cout << "   MAX LEVEL\n";
    }

    std::cout << "3. Inventory Size\n";
    std::cout << "   Level: " << inventory_level << "\n";
    std::cout << "   Effect: +" << currentInv << " -> +" << nextInv << " inventory slots\n";

    if (inventory_level < 10)
    {
        std::cout << "   Cost: " << invCost << " coins\n\n";
    }
    else
    {
        std::cout << "   MAX LEVEL\n";
    }

    std::cout << "4. Multi Open\n";
    std::cout << "   Level: " << multi_open_level << "\n";
    std::cout << "   Effect: Open " << getMultiOpenAmount() << " boxes per roll\n";


    if (multi_open_level < 3)
    {
        int cost;

        if (multi_open_level == 0) cost = 15000;
        else if (multi_open_level == 1) cost = 50000;
        else cost = 100000;

        std::cout << "   Cost: " << cost << " coins\n";
    }
    else
    {
        std::cout << "   MAX LEVEL\n";
    }

    std::cout << '\n';

    std::cout << "5. Back\n\n";

    std::cout << "Enter choice: ";
}

void Upgrades::buyLuck(double& coins)
{
    if (luck_level >= 10)
    {
        std::cout << "Luck upgrade already maxed!\n";
        return;
    }

    int cost = 100 * (luck_level + 1);

    if (coins >= cost)
    {
        coins -= cost;
        luck_level += 1;
        std::cout << "Luck upgraded!\n";
    }
    else
    {
        std::cout << "Not enough coins\n";
    }
}

void Upgrades::buySell(double& coins)
{
    if (sell_level >= 10)
    {
        std::cout << "Sell multiplier already maxed!\n";
        return;
    }

    int cost = 120 * (sell_level + 1);

    if (coins >= cost)
    {
        coins -= cost;
        sell_level += 1;
        std::cout << "Sell multiplier upgraded!\n";
    }
    else
    {
        std::cout << "Not enough coins\n";
    }
}

void Upgrades::buyInventory(double& coins)
{
    if (inventory_level >= 10)
    {
        std::cout << "Inventory slots already maxed!\n";
        return;
    }

    int cost = 150 * (inventory_level + 1);

    if (coins >= cost)
    {
        coins -= cost;
        inventory_level += 1;
        std::cout << "Upgraded inventory capacity!\n";
    }
    else
    {
        std::cout << "Not enough coins\n";
    }
}

void Upgrades::buyMultiOpen(double& coins)
{
    if (multi_open_level >= 3)
    {
        std::cout << "Multi-open already maxed!\n";
        return;
    }

    int cost;

    if (multi_open_level == 0) cost = 15000;
    else if (multi_open_level == 1) cost = 50000;
    else cost = 100000;

    if (coins >= cost)
    {
        coins -= cost;
        multi_open_level++;
        std::cout << "Multi-open upgraded!\n";
    }
    else
    {
        std::cout << "Not enough coins\n";
    }
}