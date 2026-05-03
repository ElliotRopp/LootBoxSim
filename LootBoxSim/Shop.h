#include <vector>

#include "BoxType.h"
#include "Inventory.h"


#pragma once


class Shop
{
public:
	std::vector<BoxType> boxes;

	int current_box = 0;

	Shop();
	void showShop(Inventory inv,int luck);
	void loadBoxes();
	void upgradeBox(double& coins);
};