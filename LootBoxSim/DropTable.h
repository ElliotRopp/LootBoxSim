#pragma once

#include <vector>

#include "Rarity.h"
#include "Upgrades.h"


class DropTable
{
public:
	struct DropChance
	{
		Rarity rarity;
		int weight;
	};

	std::vector<DropChance> table;

	void add(Rarity rarity, int weight);
	int getChance(Rarity rarity);
	std::vector<int> getAdjustedWeight(int luck);
	int getAdjustedChance(Rarity rarity, int luck);
	Rarity roll(int luck_bonus);
};