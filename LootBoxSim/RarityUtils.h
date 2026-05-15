#pragma once

#include <string>
#include "Rarity.h"
#include <SFML/Graphics.hpp>


namespace RarityUtils
{
	std::string getColor(Rarity r);
	std::string getName(Rarity r);
	Rarity StringToRarity(std::string rarity_str);

	sf::Color getSFMLColor(Rarity r);
}