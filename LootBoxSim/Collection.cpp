#include "Collection.h"

#include <iostream>


void Collection::add(const std::string& name, Rarity rarity)
{
	if (!has(name))
	{
		discovered.insert(name);
		uniqueDiscovered++;
	}

	switch (rarity)
	{
	case Rarity::Basic: basicCount++; break;
	case Rarity::Common: commonCount++; break;
	case Rarity::Rare: rareCount++; break;
	case Rarity::Epic: epicCount++; break;
	case Rarity::Legendary: legendaryCount++; break;
	case Rarity::Mythic: mythicCount++; break;
	case Rarity::Celestial: celestialCount++; break;
	}
}


bool Collection::has(const std::string& name)
{
	return discovered.count(name) > 0;
}


int Collection::uniqueCount()
{
	return uniqueDiscovered;
}



void Collection::show()
{
	std::cout << "\n===== COLLECTION =====\n\n";

	std::cout << "Unique Items Discovered: " << uniqueCount() << "\n\n";

	std::cout << "Basic Opened: " << basicCount << '\n';
	std::cout << "Common Opened: " << commonCount << '\n';
	std::cout << "Rare Opened: " << rareCount << '\n';
	std::cout << "Epic Opened: " << epicCount << '\n';
	std::cout << "Legendary Opened: " << legendaryCount << '\n';
	std::cout << "Mythic Opened: " << mythicCount << '\n';
	std::cout << "Celestial Opened: " << celestialCount << '\n';
}


std::set<std::string>& Collection::getDiscovered()
{
	return discovered;
}

int Collection::getBasicCount() { return basicCount; }
int Collection::getCommonCount() { return commonCount; }
int Collection::getRareCount() { return rareCount; }
int Collection::getEpicCount() { return epicCount; }
int Collection::getLegendaryCount() { return legendaryCount; }
int Collection::getMythicCount() { return mythicCount; }
int Collection::getCelestialCount() { return celestialCount; }

void Collection::setCounts(int b, int c, int r, int e, int l, int m, int cel)
{
	basicCount = b;
	commonCount = c;
	rareCount = r;
	epicCount = e;
	legendaryCount = l;
	mythicCount = m;
	celestialCount = cel;
}

void Collection::setUnique(int u)
{
	uniqueDiscovered = u;
}