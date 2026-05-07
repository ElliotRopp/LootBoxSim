#include <string>
#include "DropTable.h"


#pragma once


struct BoxType
{
	std::string name;
	int price = 0;
	DropTable table;

	int common_chance;
	int rare_chance;
	int epic_chance;
	int legendary_chance;
	int mythic_chance;
	int celestial_chance;
};