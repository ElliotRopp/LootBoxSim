// LOOT BOX SIM.


// RESET THE TEXT COLOR:
// \033[0m



// PROGRESSION IS TOO FAST


/***********    IDEAS    ***********\

	* QOL changes
	* more rarities...ancient(yellow tan?), etherial(silvery), etc.)
	* open delay/animation
	* sorted inventory
	* item modifiers (Shiny, broken, etc.)
	* acheviments
	* item collectables
	* chace to roll mystery chest (mystery odds)
	* auto sell
	* GUI
	* open delay
	* increase all upgrade prices
	* auto roll
	
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
	X upgrade box instead of buying individually
	X sell all
	X combine sell and inventory
	X fix the warnings
	X better UI's
	X stay in sell and upgrade screens
	X increase upgrade costs
	X progression

/***************************************\


/***********    IN PROGRESS    ***********\

	* fix warnings
	* GUI

/*****************************************/


#include "Inventory.h"
#include "Item.h"
#include "LootBox.h"
#include "Shop.h"
#include "SaveSystem.h"
#include "Collection.h"
#include "Upgrades.h"
#include "LootBoxGUI.h"

#include <cstdlib>
#include <ctime>
#include <iostream>





void showMainMenu(const Inventory& inv, const Upgrades& upgrades, const LootBox& box, const Shop& shop)
{
	std::cout << "\n=================================\n";
	std::cout << "        LOOT BOX SIMULATOR\n";
	std::cout << "=================================\n\n";

	std::cout << "Coins: " << inv.coins
		<< "    Items: " << inv.items.size() << "\n\n";
	std::cout << "Current Box: " << shop.boxes[shop.current_box].name << "\n\n";

	std::cout << "Upgrades:\n";
	std::cout << "  Luck Level:      " << upgrades.luck_level << "\n";
	std::cout << "  Inventory Level:  " << upgrades.inventory_level << "\n";
	std::cout << "  Sell Level:      " << upgrades.sell_level << "\n";
	std::cout << "  Multi-Open Level: " << upgrades.multi_open_level << '\n';

	std::cout << "\nPity:\n";
	std::cout << "  Epic:      " << box.epic_pity << " / 15\n";
	std::cout << "  Legendary: " << box.legendary_pity << " / 40\n";
	std::cout << "  Mythic:    " << box.mythic_pity << " / 100\n";
	std::cout << "  Celestial: " << box.celestial_pity << " / 250\n";

	std::cout << "\n---------------------------------\n";

	std::cout << "  1. Open "<< shop.boxes[shop.current_box].name << "\n";
	std::cout << "  2. Shop\n";
	std::cout << "  3. Inventory/Sell\n";
	std::cout << "  4. Collection\n";
	std::cout << "  5. Upgrades\n";
	std::cout << "  6. Save & Quit\n";

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
	srand(static_cast<unsigned int>(time(0)));

	LootBoxGUI gui;

	gui.run();

	return 0;

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
			save.loadGame(file, inv, collection, box, upgrades, shop);

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
		showMainMenu(inv, upgrades, box, shop);

		std::cin >> input;

		std::cout << '\n';

		if (input == "1") //open box
		{
			BoxType& boxtype = shop.boxes[shop.current_box];

			int opens = upgrades.getMultiOpenAmount();

			for (int i = 0; i < opens; i++)
			{
				Item reward = box.open(boxtype.table, boxtype.name, collection, upgrades);

				collection.add(reward.name, reward.rarity);
				inv.addItem(reward);
			}

			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "2") //shop
		{
			shop.showShop(inv, upgrades.luck_level);

			int choice;
			std::cin >> choice;

			if (choice > 0)
			{
				if (choice == 1)
				{
					shop.upgradeBox(inv.coins);
				}
				else if(choice == 2)
				{
					continue;
				}
			}
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "3") //inventory and sell
		{
			inv.sellItem(upgrades, 1);
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "4") //collection
		{
			collection.show();
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "5") //upgrades
		{
			while (true)
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
					inv.limit = static_cast<uint64_t>(100 + upgrades.getInventoryBonus());
				}
				if (choice == 4)
				{
					upgrades.buyMultiOpen(inv.coins);
				}
				if (choice == 5)
				{
					break;
				}
			}
			
			clearInputBuffer();
			waitForEnter();
		}
		else if (input == "6") //save and quit
		{
			save.saveGame(inv, collection, box, upgrades, shop);

			std::cout << "\nGOODBYE\n";
			break;
		}
	}
	return 0;
}