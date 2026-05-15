#include "LootBox.h"
#include "Item.h"
#include "DropTable.h"
#include "RarityUtils.h"
#include "Collection.h"

#include <fstream>
#include <sstream>
#include <iostream>


void LootBox::readFile()
{
	std::ifstream file("txt files/ItemList.txt");
	std::string line;


	while (std::getline(file, line))
	{
		Rarity r;
		std::string rarity;
		std::string name;
		std::string valuestr;


		std::stringstream ss(line);

		std::getline(ss, rarity, ',');
		std::getline(ss, name, ',');
		std::getline(ss, valuestr, ',');
		int value = stoi(valuestr);

		r = RarityUtils::StringToRarity(rarity);


		if (r == Rarity::Basic)
		{
			basic.push_back(Item(name, r, value));
		}
		if (r == Rarity::Common)
		{
			common.push_back(Item(name, r, value));
		}
		if (r == Rarity::Rare)
		{
			rare.push_back(Item(name, r, value));
		}
		if (r == Rarity::Epic)
		{
			epic.push_back(Item(name, r, value));
		}
		if (r == Rarity::Legendary)
		{
			legendary.push_back(Item(name, r, value));
		}
		if (r == Rarity::Mythic)
		{
			mythic.push_back(Item(name, r, value));
		}
		if (r == Rarity::Celestial)
		{
			celestial.push_back(Item(name, r, value));
		}
	}

	if (file.is_open())
	{
		std::cout << "Loaded "
			<< common.size() << " commons, "
			<< rare.size() << " rares, "
			<< epic.size() << " epics, "
			<< legendary.size() << " legendaries, "
			<< mythic.size() << " mythics, "
			<< celestial.size() << " celestials\n";
	}

	file.close();
}


Item LootBox::open(DropTable& table, const std::string& box_name, Collection& collection, Upgrades& upgrades)
{
	Item item;
	bool pity_triggered = false;

	if (celestial_pity >= 250 && table.supports(Rarity::Celestial))
	{
		mythic_pity = 0;
		legendary_pity = 0;
		epic_pity = 0;
		celestial_pity = 0;

		item = celestial[rand() % celestial.size()];
		pity_triggered = true;
	}
	if (mythic_pity >= 100 && box_name != "Free Box" && box_name != "Basic Box" && box_name != "Gold Box" && box_name != "Lucky Box")
	{
		mythic_pity = 0;
		legendary_pity = 0;
		epic_pity = 0;

		item = mythic[rand() % mythic.size()];
		pity_triggered = true;
	}
	if (legendary_pity >= 40 && box_name != "Free Box" && box_name != "Basic Box")
	{
		legendary_pity = 0;
		epic_pity = 0;

		item = legendary[rand() % legendary.size()];
		pity_triggered = true;
	}
	if (epic_pity >= 15 && table.supports(Rarity::Epic))
	{
		epic_pity = 0;

		item = epic[rand() % epic.size()];
		pity_triggered = true;
	}
	if (celestial_pity >= 250)
	{
		celestial_pity = 0;
		//mythic_pity = 0;
		//legendary_pity = 0;
		//epic_pity = 0;
	}
	if (mythic_pity >= 100)
	{
		mythic_pity = 0;
		//legendary_pity = 0;
		//epic_pity = 0;
	}
	if (legendary_pity >= 40)
	{
		legendary_pity = 0;
		//epic_pity = 0;
	}
	if (epic_pity >= 15)
	{
		epic_pity = 0;
	}


	if (!pity_triggered)
	{
		Rarity r = table.roll(upgrades.luck_level, box_name);

		if (r == Rarity::Basic)
		{
			item = basic[rand() % basic.size()];
		}
		else if (r == Rarity::Common)
		{
			item = common[rand() % common.size()];
		}
		else if (r == Rarity::Rare)
		{
			item = rare[rand() % rare.size()];
		}
		else if (r == Rarity::Epic)
		{
			item = epic[rand() % epic.size()];
		}
		else if (r == Rarity::Legendary)
		{
			item = legendary[rand() % legendary.size()];
		}
		else if (r == Rarity::Mythic)
		{
			item = mythic[rand() % mythic.size()];
		}
		else if (r == Rarity::Celestial)
		{
			item = celestial[rand() % celestial.size()];
		}
	}

		if (item.rarity == Rarity::Epic)
		{
			epic_pity = 0;
		}
		if (item.rarity == Rarity::Legendary)
		{
			legendary_pity = 0;
		}
		if (item.rarity == Rarity::Mythic)
		{
			mythic_pity = 0;
		}
		if (item.rarity == Rarity::Celestial)
		{
			celestial_pity = 0;
		}


		epic_pity++;
		legendary_pity++;
		mythic_pity++;
		celestial_pity++;

		std::cout << "\nOpened " << box_name << '\n';


		std::cout << "\nRolled: "
			<< RarityUtils::getColor(item.rarity)
			<< item.name << " ("
			<< item.value << ")"
			<< "\033[0m";
			
		if (!collection.has(item.name))
		{
			std::cout << " [NEW]\n";
		}

		return item;
}


LootBox::LootBox()
{
	readFile();
}