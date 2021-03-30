#pragma once
#include "GameItem.generated.h"

UENUM(BlueprintType)
enum class EGameItem: uint8
{
  None,
  Money,
  Scissors,
  Potion,
  Letter,
  Book,
  Candle,
  Bottle,
  Door
};
