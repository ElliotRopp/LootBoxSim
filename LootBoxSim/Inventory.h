#include <string>
#include <vector>

#include "Item.h"
#include "Upgrades.h"

#pragma once

class Inventory
{
public:
	std::vector<Item> items;
	int coins = 0;

	int limit = 100;
	int count = 0;

	void addItem(Item item);
	void showInventory();
	void sellItem(Upgrades& upgrade);
};
