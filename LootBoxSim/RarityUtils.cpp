#include "RarityUtils.h"


std::string RarityUtils::getColor(Rarity r)
{
	switch (r)
	{
        case Rarity::Basic:     return "\033[90m";
        case Rarity::Common:    return "\033[32m";
        case Rarity::Rare:      return "\033[34m";
        case Rarity::Epic:      return "\033[35m";
        case Rarity::Legendary: return "\033[33m";
        case Rarity::Mythic:    return "\033[91m";
    }

    return "\033[0m";
}


std::string RarityUtils::getName(Rarity r)
{
    switch(r)
    {
        case Rarity::Basic:     return "Basic";
        case Rarity::Common:    return "Common";
        case Rarity::Rare:      return "Rare";
        case Rarity::Epic:      return "Epic";
        case Rarity::Legendary: return "Legendary";
        case Rarity::Mythic:    return "Mythic";
    }

    return "Unknown";
}


Rarity RarityUtils::StringToRarity(std::string rarity_str)
{
    if (rarity_str == "Basic")       return Rarity::Basic;
    else if (rarity_str == "Common") return Rarity::Common;
    else if (rarity_str == "Rare")   return Rarity::Rare;
    else if (rarity_str == "Epic")   return Rarity::Epic;
    else if (rarity_str == "Legendary") return Rarity::Legendary;
    else if (rarity_str == "Mythic") return Rarity::Mythic;

    return Rarity::Common;
}