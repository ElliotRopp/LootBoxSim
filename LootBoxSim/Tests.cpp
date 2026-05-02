#include "Inventory.h"
#include "Item.h"
#include "LootBox.h"

#include <cstdlib>
#include <ctime>
#include <iostream>



int main()
{
	LootBox box;

	for (int i = 0; i < box.common.size(); i++)
	{
		Item curr = box.common[i];
		std::cout << curr.name << '\n';
	}

	return 0;
}