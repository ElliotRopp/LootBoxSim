// LOOT BOX SIM.


// RESET THE TEXT COLOR:
// \033[0m


/***********    IDEAS    ***********\

	* progression/goal
	* QOL changes
	* make into an application?
	* more rarities...(celestial(cyan), ancient(yellow tan?), etherial(silvery), etc.)
	* open delay/animation
	* sorted inventory
	* item modifiers (Shiny, broken, etc.)
	* acheviments
	* item collectables
	* chace to roll mystery chest (mystery odds)
	* auto sell
	* fix the warnings
	* click on buttons instead of typing?
	* upgrade box instead of buying individually
	
/***********************************/


/***********    COMPLETE    ***********\

	X shop/free box
	X show drop chances
	X item limit
	X save system
	X multi sell
	X more boxes
	X bulk sell
	X pity
	X index
	X revamp save system
	X save pity
	X upgrades

/***************************************\


/***********    IN PROGRESS    ***********\

	* balancing - upgrades, costs, chances, etc.
	* better UI's
	
/*****************************************/


#include "Inventory.h"
#include "Item.h"
#include "LootBox.h"
#include "Shop.h"
#include "SaveSystem.h"
#include "Collection.h"
#include "Upgrades.h"

#include <cstdlib>
#include <ctime>
#include <iostream>





void showMainMenu(const Inventory& inv, const Upgrades& upgrades, const LootBox& box)
{
	std::cout << "\n=================================\n";
	std::cout << "        LOOT BOX SIMULATOR\n";
	std::cout << "=================================\n\n";

	std::cout << "Coins: " << inv.coins
		<< "    Items: " << inv.count << "\n\n";

	std::cout << "Upgrades:\n";
	std::cout << "  Luck Level:      " << upgrades.luck_level << "\n";
	std::cout << "  Inventory Level:  " << upgrades.inventory_level << "\n";
	std::cout << "  Sell Level:      " << upgrades.sell_level << "\n";
	std::cout << "  Multi-Open Level: " << upgrades.multi_open_level << '\n';

	std::cout << "\nPity:\n";
	std::cout << "  Epic:      " << box.epic_pity << " / 15\n";
	std::cout << "  Legendary: " << box.legendary_pity << " / 40\n";
	std::cout << "  Mythic:    " << box.mythic_pity << " / 100\n";

	std::cout << "\n---------------------------------\n";

	std::cout << "  1. Open Box\n";
	std::cout << "  2. Shop\n";
	std::cout << "  3. Inventory\n";
	std::cout << "  4. Sell\n";
	std::cout << "  5. Collection\n";
	std::cout << "  6. Upgrades\n";
	std::cout << "  7. Save & Quit\n";

	std::cout << "---------------------------------\n";

	std::cout << "Enter choice: ";
}



void waitForEnter()
{
	std::cout << "\n=================================\n";
	std::cout << "        PRESS ENTER TO CONTINUE\n";
	std::cout << "=================================\n";

	std::cin.get();
}


void clearInputBuffer()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}




int main()
{
	srand(time(0));

	Inventory inv;
	LootBox box;
	Shop shop;
	SaveSystem save;
	Collection collection;
	Upgrades upgrades;

	std::string input;
	int continue_choice;

	std::cout << "=================================\n";
	std::cout << "        LOOT BOX SIMULATOR\n";
	std::cout << "=================================\n\n";

	std::cout << "1. New Game\n";
	std::cout << "2. Continue\n\n";

	std::cout << "Select Option: ";

	std::cin >> continue_choice;

	if (continue_choice == 2)
	{
		std::vector<std::string> save_files = save.getSaveFiles();

		if (save_files.empty())
		{
			std::cout << "No saves found.\n";
			inv.items.clear();
			inv.coins = 0;
			save.current_save = "";
		}
		else
		{
			std::string file = save.chooseSave(save_files);
			save.loadGame(file, inv, collection, box, upgrades);

			std::cout << "\nLoading data...\n";

			save.current_save = file;
		}
	}
	else if (continue_choice == 1)
	{
		inv.items.clear();
		inv.coins = 0;

		save.current_save = "";
	}


	while (true)
	{
		showMainMenu(inv, upgrades, box);

		std::cin >> input;

		std::cout << '\n';

		if (input == "1")
		{
			BoxType boxtype = shop.boxes[0];
			//Item reward = box.open(shop.boxes[0].table, "Free Box", collection, inv, upgrades);

			int opens = upgrades.getMultiOpenAmount();

			for (int i = 0; i < opens; i++)
			{
				Item reward = box.open(shop.boxes[0].table, "Free Box", collection, inv, upgrades);

				collection.add(reward.name, reward.rarity);
				inv.addItem(reward);
			}

			//collection.add(reward.name, reward.rarity);

			//inv.addItem(reward);
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "2")
		{
			shop.showShop(inv, upgrades.luck_level);

			int choice;
			std::cin >> choice;

			if (choice >= 0 && choice < shop.boxes.size())
			{
				BoxType boxtype = shop.boxes[choice];

				if (inv.coins >= boxtype.price)
				{
					inv.coins -= boxtype.price;

					//Item reward = box.open(boxtype.table, boxtype.name, collection, inv, upgrades);

					//collection.add(reward.name, reward.rarity);

					//inv.addItem(reward);

					int opens = upgrades.getMultiOpenAmount();

					for (int i = 0; i < opens; i++)
					{
						Item reward = box.open(boxtype.table, boxtype.name, collection, inv, upgrades);

						collection.add(reward.name, reward.rarity);
						inv.addItem(reward);
					}
				}
				else
				{
					std::cout << "\nNOT ENOUGH COINS!\n";
				}
			}
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "3")
		{
			inv.showInventory();
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "4")
		{
			inv.showInventory();
			inv.sellItem(upgrades);
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "5")
		{
			collection.show();
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "6")
		{
			upgrades.show(inv.coins);

			int choice;
			std::cin >> choice;

			if (choice == 1)
			{
				upgrades.buyLuck(inv.coins);
			}
			if (choice == 2)
			{
				upgrades.buySell(inv.coins);
			}
			if (choice == 3)
			{
				upgrades.buyInventory(inv.coins);
				inv.limit = 100 + upgrades.getInventoryBonus();
			}
			if (choice == 4)
			{
				upgrades.buyMultiOpen(inv.coins);
			}
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "7")
		{
			save.saveGame(inv, collection, box, upgrades);

			std::cout << "\nGOODBYE\n";
			break;
		}
	}
	return 0;
}