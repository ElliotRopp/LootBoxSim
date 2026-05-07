#include <string>

#include "Rarity.h"

#pragma once

class Item
{
public:
	std::string name;
	Rarity rarity = Rarity::Basic;
	int value = -999999;

	Item() {};
	Item(std::string n, Rarity r, int v)
	{
		name = n;
		rarity = r;
		value = v;
	}
};