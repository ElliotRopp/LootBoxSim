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
	void show(double coins);
	void buyLuck(double& coins);
	void buySell(double& coins);
	void buyInventory(double& coins);
	void buyMultiOpen(double& coins);
};