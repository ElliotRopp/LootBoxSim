#include "DropTable.h"
#include "Upgrades.h"

#include <cstdlib>


void DropTable::add(Rarity rarity, int weight)
{
	table.push_back({ rarity, weight });
}



int DropTable::getChance(Rarity rarity)
{
	int total = 0;

	for (const auto& entry : table)
		total += entry.weight;

	if (total == 0) return 0;

	for (const auto& entry : table)
	{
		if (entry.rarity == rarity)
		{
			return (entry.weight * 100) / total;
		}
	}

	return 0;
}


Rarity DropTable::roll(int luck_bonus, const std::string& box_name)
{
	auto adjusted = getAdjustedWeight(luck_bonus, box_name);

	int total_weight = 0;
	for (int w : adjusted)
		total_weight += w;

	if (total_weight <= 0)
		return Rarity::Common;

	int roll = rand() % total_weight;

	for (size_t i = 0; i < adjusted.size(); i++)
	{
		if (roll < adjusted[i])
			return table[i].rarity;

		roll -= adjusted[i];
	}

	return Rarity::Common;
}


std::vector<int> DropTable::getAdjustedWeight(int luck, const std::string& box_name)
{
	std::vector<int> adjusted;

	for (auto& entry : table)
	{
		adjusted.push_back(entry.weight);
	}

	int steal = luck; 
	int give = std::min(luck * 2, 10);  

	bool earlyBox =
		box_name == "Free Box" ||
		box_name == "Basic Box";

	int epicBoost = earlyBox ? give / 3 : give / 2;
	int legendaryBoost = earlyBox ? give / 5 : give / 3;
	int mythicBoost = earlyBox ? give / 10 : give / 4;
	int celestialBoost = earlyBox ? 0 : give / 6;

	for (size_t i = 0; i < table.size() && steal > 0; i++)
	{
		if (table[i].rarity == Rarity::Basic ||
			table[i].rarity == Rarity::Common)
		{
			int take = std::min(adjusted[i], steal);
			adjusted[i] -= take;
			steal -= take;
		}
	}

	for (size_t i = 0; i < table.size(); i++)
	{
		switch (table[i].rarity)
		{
		case Rarity::Rare:
			adjusted[i] += give;
			break;

		case Rarity::Epic:
			adjusted[i] += epicBoost;
			break;

		case Rarity::Legendary:
			adjusted[i] += legendaryBoost;
			break;

		case Rarity::Mythic:
			adjusted[i] += mythicBoost;
			break;

		case Rarity::Celestial:
			adjusted[i] += celestialBoost;
			break;

		default:
			break;
		}
	}

	return adjusted;

	//std::vector<int> adjusted;

	//for (auto& entry : table)
	//{
	//	adjusted.push_back(entry.weight);
	//}

	//int steal = luck * 2;

	//for (size_t i = 0; i < table.size() && steal > 0; i++)
	//{
	//	if (table[i].rarity == Rarity::Basic ||
	//		table[i].rarity == Rarity::Common)
	//	{
	//		int take = std::min(adjusted[i], steal);
	//		adjusted[i] -= take;
	//		steal -= take;
	//	}
	//}

	//int give = luck * 2;

	//for (size_t i = 0; i < table.size() && give > 0; i++)
	//{
	//	if (table[i].rarity == Rarity::Rare)
	//	{
	//		adjusted[i] += give / 4;
	//	}
	//	else if (table[i].rarity == Rarity::Epic)
	//	{
	//		adjusted[i] += give / 4;
	//	}
	//	else if (table[i].rarity == Rarity::Legendary)
	//	{
	//		adjusted[i] += give / 4;
	//	}
	//	else if (table[i].rarity == Rarity::Mythic)
	//	{
	//		adjusted[i] += give / 4;
	//	}
	//	else if (table[i].rarity == Rarity::Celestial)
	//	{
	//		adjusted[i] += give / 4;
	//	}
	//}

	//return adjusted;
}


int DropTable::getAdjustedChance(Rarity rarity, int luck, const std::string& box_name)
{
	auto adjusted = getAdjustedWeight(luck, box_name);

	int total = 0;
	int target = 0;

	for (size_t i = 0; i < table.size(); i++)
	{
		total += adjusted[i];

		if (table[i].rarity == rarity)
			target = adjusted[i];
	}

	if (total == 0)
		return 0;

	return (target * 100) / total;
}


bool DropTable::supports(Rarity r)
{
	for (auto& entry : table)
	{
		if (entry.rarity == r)
			return entry.weight > 0;
	}
	return false;
}