#pragma once
#include "GameEventType.generated.h"

UENUM(BlueprintType)
enum class EGameEventType: uint8
{
  TakeItem,
  RemoveItem,
  RestartDialog,
  NoAction
};

// String to Enum
static EGameEventType GetActionFromString(const FString & Name)
{
  FString Action = Name.ToLower();
  if (Action.Equals("takeitem"))
    return EGameEventType::TakeItem;
  else if (Action.Equals("removeitem"))
    return EGameEventType::RemoveItem;
  else if (Action.Equals("restartdialog"))
    return EGameEventType::RestartDialog;

  return EGameEventType::NoAction;
}