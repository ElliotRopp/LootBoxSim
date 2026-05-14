#include <string>
#include <vector>

#include "Item.h"
#include "Upgrades.h"

#pragma once

class Inventory
{
public:
	std::vector<Item> items;
	double coins = 0;

	uint64_t limit = 100;

	void addItem(Item item);
	void showInventory();
	void sellItem(Upgrades& upgrade, int option);
};
