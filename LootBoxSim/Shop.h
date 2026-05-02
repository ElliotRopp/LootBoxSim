#include <vector>

#include "BoxType.h"
#include "Inventory.h"


#pragma once


class Shop
{
private:
	void initBoxes();

public:
	std::vector<BoxType> boxes;

	Shop();
	void showShop(Inventory inv,int luck);
	void loadBoxes();
};