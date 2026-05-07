#include "SaveSystem.h"
#include "RarityUtils.h"
#include "Upgrades.h"
#include "Shop.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>



std::vector<std::string> SaveSystem::getSaveFiles()
{
	std::vector<std::string> saves;

	for (const auto& entry : std::filesystem::directory_iterator("saves"))
	{
		saves.push_back(entry.path().filename().string());
	}

	return saves;
}


std::string SaveSystem::chooseSave(const std::vector<std::string>& saves)
{
	int choice;

	std::cout << '\n';

	std::cout << "\n=================================\n";
	std::cout << "           SAVE FILES\n";
	std::cout << "=================================\n\n";

	for (int i = 0; i < saves.size(); i++)
	{
		std::cout << i + 1 << ". " << saves[i] << std::endl;
	}

	std::cout << "\nSelect Save: ";

	std::cin >> choice;
	std::cout << "\n";

	return "saves/" + saves[choice - 1];
}


void SaveSystem::loadGame(std::string filename, Inventory& inv, Collection& collection, LootBox& box, Upgrades& upgrades, Shop& shop)
{
	std::ifstream file(filename);

	if (!file)
	{
		std::cout << "Error loading save.\n";
		return;
	}

	inv.items.clear();

	std::string line;

	while (std::getline(file, line))
	{
		if (line.rfind("COINS:", 0) == 0)
		{
			inv.coins = std::stoi(line.substr(6));
		}

		else if (line.rfind("BOX:", 0) == 0)
		{
			shop.current_box = std::stoi(line.substr(4));
		}

		else if (line.rfind("PITY:", 0) == 0)
		{
			line.erase(0, 5);

			std::stringstream ss(line);
			char comma;

			ss >> box.epic_pity >> comma
				>> box.legendary_pity >> comma
				>> box.mythic_pity;
		}

		else if (line.rfind("COLLECTION:", 0) == 0)
		{
			std::string data = line.substr(11);
			std::stringstream ss(data);

			int u, b, c, r, e, l, m, cel;
			char comma;

			ss >> u >> comma
				>> b >> comma
				>> c >> comma
				>> r >> comma
				>> e >> comma
				>> l >> comma
				>> m >> comma
				>> cel;

			collection.setUnique(u);
			collection.setCounts(b, c, r, e, l, m, cel);
		}

		else if (line.rfind("UPGRADES:", 0) == 0)
		{
			std::string data = line.substr(9);

			std::stringstream ss(data);
			char comma;

			ss >> upgrades.luck_level >> comma
				>> upgrades.inventory_level >> comma
				>> upgrades.sell_level >> comma
				>> upgrades.multi_open_level;
		}

		else if (line == "INVENTORY:")
		{
			while (std::getline(file, line))
			{
				if (line.empty())
					continue;

				std::stringstream ss(line);

				std::string rarity;
				std::string name;
				std::string valueStr;

				getline(ss, rarity, ',');
				getline(ss, name, ',');
				getline(ss, valueStr);

				if (rarity.empty() || name.empty() || valueStr.empty())
					continue;

				int value = std::stoi(valueStr);

				Rarity r = RarityUtils::StringToRarity(rarity);

				inv.items.push_back(Item(name, r, value));
			}
		}
	}
}


void SaveSystem::saveGame(Inventory& inv, Collection& collection, LootBox& box, Upgrades& upgrades, Shop& shop)
{
	if (current_save == "")
	{
		std::string name;
		std::cout << "Enter save name: ";
		std::cin >> name;

		current_save = "saves/" + name + ".txt";
	}

	std::ofstream file(current_save, std::ios::trunc);

	if (!file)
	{
		std::cout << "Save failed.\n";
		return;
	}

	file << "COINS:" << inv.coins << "\n";

	file << "BOX:" << shop.current_box << "\n";

	file << "PITY:"
		<< box.epic_pity << ","
		<< box.legendary_pity << ","
		<< box.mythic_pity << ","
		<< box.celestial_pity << "\n";


	file << "COLLECTION:"
		<< collection.uniqueCount() << ","
		<< collection.getBasicCount() << ","
		<< collection.getCommonCount() << ","
		<< collection.getRareCount() << ","
		<< collection.getEpicCount() << ","
		<< collection.getLegendaryCount() << ","
		<< collection.getMythicCount() << ","
		<< collection.getCelestialCount() << "\n";

	file << "UPGRADES:"
		<< upgrades.luck_level << ","
		<< upgrades.inventory_level << ","
		<< upgrades.sell_level << ","
		<< upgrades.multi_open_level << '\n';

	file << "INVENTORY:\n";

	for (auto& item : inv.items)
	{
		file << RarityUtils::getName(item.rarity) << ","
			<< item.name << ","
			<< item.value << "\n";
	}

	std::cout << "Game saved!\n";
}