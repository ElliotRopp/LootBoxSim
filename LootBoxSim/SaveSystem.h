#pragma once

#include "Inventory.h"
#include "Collection.h"
#include "LootBox.h"
#include "Upgrades.h"
#include "Shop.h"

#include <string>
#include <vector>



class SaveSystem
{
public:
	std::string current_save = "";
	std::vector<std::string> getSaveFiles();
	std::string chooseSave(const std::vector<std::string>& saves);
	void saveGame(Inventory& inv, Collection& collection, LootBox& box, Upgrades& upgrades, Shop& shop);
	void loadGame(std::string filename, Inventory& inv, Collection& collection, LootBox& box, Upgrades& upgrades, Shop& shop);
};