#include <vector>

#include "Item.h"
#include "BoxType.h"
#include "DropTable.h"
#include "Collection.h"
#include "Inventory.h"


#pragma once

class LootBox
{
public:
	std::vector<Item> basic;
	std::vector<Item> common;
	std::vector<Item> rare;
	std::vector<Item> epic;
	std::vector<Item> legendary;
	std::vector<Item> mythic;
	std::vector<Item> celestial;

	int epic_pity = 0;
	int legendary_pity = 0;
	int mythic_pity = 0;
	int celestial_pity = 0;

	LootBox();
	Item open(DropTable& table, const std::string& box_name, Collection& collection, Inventory& inv, Upgrades& upgrades);
	void readFile();
};