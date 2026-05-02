#pragma once


class Upgrades
{
public:
	int luck_level = 0;
	int inventory_level = 0;
	int sell_level = 0;
	int multi_open_level = 0;

	int getLuckBonus();
	double getSellBonus();
	int getInventoryBonus();
	int getMultiOpenAmount();
	void show(int coins);
	void buyLuck(int& coins);
	void buySell(int& coins);
	void buyInventory(int& coins);
	void buyMultiOpen(int& coins);
};