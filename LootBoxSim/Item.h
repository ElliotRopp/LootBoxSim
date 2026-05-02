#include <string>

#include "Rarity.h"

//#define RESET   "\033[0m"
//#define RED     "\033[31m"
//#define GREEN   "\033[32m"
//#define YELLOW  "\033[33m"
//#define BLUE    "\033[34m"
//#define MAGENTA "\033[35m"
//#define CYAN    "\033[36m"

#pragma once

class Item
{
public:
	std::string name;
	Rarity rarity;
	int value;

	Item() {}
	Item(std::string n, Rarity r, int v)
	{
		name = n;
		rarity = r;
		value = v;
	}

	//std::string getColor() const
	//{
	//	if (rarity == Rarity::Common) return GREEN;
	//	if (rarity == Rarity::Rare) return BLUE;
	//	if (rarity == Rarity::Epic) return MAGENTA;
	//	if (rarity == Rarity::Legendary) return YELLOW;
	//}
};