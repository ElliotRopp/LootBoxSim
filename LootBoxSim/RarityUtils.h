#include <string>
#include "Rarity.h"

#pragma once


namespace RarityUtils
{
	std::string getColor(Rarity r);
	std::string getName(Rarity r);
	Rarity StringToRarity(std::string rarity_str);
}