#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Shop.h"
#include "BoxType.h"
#include "Inventory.h"
#include "RarityUtils.h"


Shop::Shop()
{ 
	loadBoxes();
}


void Shop::loadBoxes()
{
	std::ifstream file("txt files/Boxes.txt");
	std::string line;

	if (!file)
	{
		std::cout << "Failed to open Boxes.txt\n";
		return;
	}

	while (std::getline(file, line))
	{
		std::stringstream ss(line);

		std::string name;
		std::string priceStr;

		std::string basicStr;
		std::string commonStr;
		std::string rareStr;
		std::string epicStr;
		std::string legendaryStr;
		std::string mythicStr;

		getline(ss, name, ',');
		getline(ss, priceStr, ',');
		getline(ss, basicStr, ',');
		getline(ss, commonStr, ',');
		getline(ss, rareStr, ',');
		getline(ss, epicStr, ',');
		getline(ss, legendaryStr, ',');
		getline(ss, mythicStr);

		BoxType box;

		box.name = name;
		box.price = stoi(priceStr);

		int basic = stoi(basicStr);
		int common = stoi(commonStr);
		int rare = stoi(rareStr);
		int epic = stoi(epicStr);
		int legendary = stoi(legendaryStr);
		int mythic = stoi(mythicStr);

		if (basic > 0) box.table.add(Rarity::Basic, basic);
		if (common > 0) box.table.add(Rarity::Common, common);
		if (rare > 0) box.table.add(Rarity::Rare, rare);
		if (epic > 0) box.table.add(Rarity::Epic, epic);
		if (legendary > 0) box.table.add(Rarity::Legendary, legendary);
		if (mythic > 0) box.table.add(Rarity::Mythic, mythic);

		boxes.push_back(box);
	}

	std::cout << "Loaded " << boxes.size() << " boxes.\n";
}


void Shop::showShop(Inventory inv, int luck)
{
	std::cout << "\n===== SHOP =====\n";

	std::cout << "Coins: " << inv.coins << '\n';
	std::cout <<  '\n';

	for (int i = 1; i < boxes.size(); i++)
	{
		std::cout << '\n' << i << ": "
			<< boxes[i].name
			<< "      (" << boxes[i].price << " coins)\n";

		std::cout << "   "
			<< boxes[i].table.getAdjustedChance(Rarity::Basic, luck) << "% \033[90mBasic\033[0m | "
			<< boxes[i].table.getAdjustedChance(Rarity::Common, luck) << "% \033[32mCommon\033[0m | "
			<< boxes[i].table.getAdjustedChance(Rarity::Rare, luck) << "% \033[34mRare\033[0m | "
			<< boxes[i].table.getAdjustedChance(Rarity::Epic, luck) << "% \033[35mEpic\033[0m | "
			<< boxes[i].table.getAdjustedChance(Rarity::Legendary, luck) << "% \033[33mLegendary\033[0m | "
			<< boxes[i].table.getAdjustedChance(Rarity::Mythic, luck) << "% \033[91mMythic\033[0m\n";
	}
	std::cout << '\n' << boxes.size() << ". Back to menu\n";
}