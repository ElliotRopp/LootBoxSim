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


Rarity DropTable::roll(int luck_bonus)
{
	auto adjusted = getAdjustedWeight(luck_bonus);

	int total_weight = 0;
	for (int w : adjusted)
		total_weight += w;

	if (total_weight == 0)
		return Rarity::Common;

	int roll = rand() % total_weight;

	for (size_t i = 0; i < adjusted.size(); i++)
	{
		if (roll < adjusted[i])
			return table[i].rarity;

		roll -= adjusted[i];
	}

	return Rarity::Common;
	
	//int total_weight = 0;

	//std::vector<int> adjusted_weights;

	//for (auto& entry : table)
	//{
	//	int weight = entry.weight;

	//	if (entry.rarity == Rarity::Rare)
	//	{
	//		weight += luck_bonus;
	//	}
	//	if (entry.rarity == Rarity::Epic)
	//	{
	//		weight += luck_bonus * 2;
	//	}

	//	if (entry.rarity == Rarity::Legendary)
	//	{
	//		weight += luck_bonus * 3;
	//	}

	//	if (entry.rarity == Rarity::Mythic)
	//	{
	//		weight += luck_bonus * 4;
	//	}
	//	adjusted_weights.push_back(weight);
	//	total_weight += weight;
	//}

	//if (total_weight == 0)
	//{
	//	return Rarity::Common;
	//}

	//int roll = rand() % total_weight;

	//for (int i = 0; i < table.size(); i++)
	//{
	//	if (roll < adjusted_weights[i])
	//	{
	//		return table[i].rarity;
	//	}

	//	roll -= adjusted_weights[i];
	//}

	//return Rarity::Common;
}


std::vector<int> DropTable::getAdjustedWeight(int luck)
{

	std::vector<int> adjusted;

	for (auto& entry : table)
	{
		adjusted.push_back(entry.weight);
	}

	int steal = luck * 2;

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

	int give = luck * 2;

	for (size_t i = 0; i < table.size() && give > 0; i++)
	{
		if (table[i].rarity == Rarity::Rare)
		{
			adjusted[i] += give / 4;
		}
		else if (table[i].rarity == Rarity::Epic)
		{
			adjusted[i] += give / 4;
		}
		else if (table[i].rarity == Rarity::Legendary)
		{
			adjusted[i] += give / 4;
		}
		else if (table[i].rarity == Rarity::Mythic)
		{
			adjusted[i] += give / 4;
		}
	}

	return adjusted;

	//for (auto& entry : table)
	//{
	//	if (entry.rarity == rarity)
	//	{
	//		int weight = entry.weight;

	//		if (weight == 0)
	//			return 0;

	//		if (rarity == Rarity::Rare)
	//			weight += luck;

	//		if (rarity == Rarity::Epic)
	//			weight += luck * 2;

	//		if (rarity == Rarity::Legendary)
	//			weight += luck * 3;

	//		if (rarity == Rarity::Mythic)
	//			weight += luck * 4;

	//		return weight;
	//	}
	//}

	//return 0;
}


int DropTable::getAdjustedChance(Rarity rarity, int luck)
{
	auto adjusted = getAdjustedWeight(luck);

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