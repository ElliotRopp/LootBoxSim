#pragma once

#include <vector>
#include <string>

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
	std::vector<int> getAdjustedWeight(int luck, const std::string& box_name);
	int getAdjustedChance(Rarity rarity, int luck, const std::string& box_name);
	Rarity roll(int luck_bonus, const std::string& box_name);
	int getRarityTier(Rarity r);
	bool supports(Rarity r);
};