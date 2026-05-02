#include <iostream>
#include <algorithm>

#include "Inventory.h"
#include "RarityUtils.h"
#include "Upgrades.h"


void Inventory::addItem(Item item)
{
	if (count < limit)
	{
		items.push_back(item);
		count++;
	}
	else
	{
		std::cout << "Inventory full!\n";
	}
}


void Inventory::showInventory()
{
	std::cout << "\n=== INVENTORY ===\n";

	for (int i = 0; i < items.size(); i++)
	{
		std::cout << i << ": " << RarityUtils::getColor(items[i].rarity) 
			<< RarityUtils::getName(items[i].rarity) << ' '
			<< items[i].name
			<< " (" << items[i].value << ")\033[0m\n";
	}
	std::cout << "Coins: " << coins << '\n'
		<< "Items: " << count << '\n';
}


void Inventory::sellItem(Upgrades& upgrade)
{
	if (items.empty())
	{
		std::cout << "Invetory is empty!\n:";
		return;
	}

	std::vector<int> indices;
	int choice; 

	std::cout << "\nSell all Basics (-2)\n";
	std::cout << "Sell all Commons (-3)\n";
	std::cout << "Enter the idexes of the items you want to sell with a space separating each one (-1 to finish): ";

	while (std::cin >> choice && choice != -1)
	{
		if (choice == -2)
		{
			int total = 0;
			for (int i = items.size() - 1; i >= 0; i--)
			{
				if (items[i].rarity == Rarity::Basic)
				{
					total += items[i].value;
					items.erase(items.begin() + i);
					count--;
				}
			}
			std::cout << "Sold all Basics for " << total * upgrade.getSellBonus() << " coins\n";
			coins += total * upgrade.getSellBonus();
			return;
		}
		if (choice == -3)
		{
			int total = 0;
			for (int i = items.size() - 1; i >= 0; i--)
			{
				if (items[i].rarity == Rarity::Common)
				{
					total += items[i].value;
					items.erase(items.begin() + i);
					count--;
				}
			}
			std::cout << "\nSold all Commons for " << total * upgrade.getSellBonus() << " coins\n";
			coins += total;
			return;
		}

		if (choice > count)
		{
			std::cout << "Item doesn't exist!\n";
		}
		else
		{
			indices.push_back(choice);
		}
	}

	
	if (indices.empty())
	{
		std::cout << "No items selected.\n";
		return;
	}

	std::sort(indices.rbegin(), indices.rend());

	int total = 0;

	std::cout << '\n';

	for (int i : indices)
	{
		if (i >= 0 && i < items.size())
		{
			std::cout << "Sold: " << RarityUtils::getColor(items[i].rarity) << items[i].name << "\033[0m\n";

			total += items[i].value;
			items.erase(items.begin() + i);
			count--;
		}
	}


	std::cout << "\n+" << total * upgrade.getSellBonus() << " coins\n";

	coins += total * upgrade.getSellBonus();
}