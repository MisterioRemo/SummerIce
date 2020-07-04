#pragma once
#include "GameItem.generated.h"

UENUM(BlueprintType)
enum class SUMMERICE_API EGameItem : uint8
{
	None,
	Money,
	Scissors,
	Potion,
	Letter,
	Book,
	Candle,
	Bottle
};
