#pragma once

#include <set>
#include <string>

#include "Rarity.h"

class Collection
{
private:
    std::set<std::string> discovered;

    int uniqueDiscovered = 0;
    int basicCount = 0;
    int commonCount = 0;
    int rareCount = 0;
    int epicCount = 0;
    int legendaryCount = 0;
    int mythicCount = 0;
    int celestialCount = 0;

public:
    Collection() {};

	void add(const std::string& name, Rarity rarity);
	bool has(const std::string& name);
    int uniqueCount();
	void show();

    std::set<std::string>& getDiscovered();

    int getBasicCount();
    int getCommonCount();
    int getRareCount();
    int getEpicCount();
    int getLegendaryCount();
    int getMythicCount();
    int getCelestialCount();

    void setUnique(int u);
    void setCounts(int b, int c, int r, int e, int l, int m, int cel);
};