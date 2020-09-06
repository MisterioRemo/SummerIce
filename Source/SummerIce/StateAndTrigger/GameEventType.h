#pragma once
#include "GameEventType.generated.h"

UENUM(BlueprintType)
enum class EGameEventType: uint8
{
  TakeItem,
  RemoveItem,
  RestartDialog,
  Teleport,
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
  else if (Action.Equals("teleport"))
    return EGameEventType::Teleport;

  return EGameEventType::NoAction;
}

UENUM(BlueprintType)
enum class ETeleportLocation: uint8
{
  HomeFrontDoor,
  HomeHallwayRightDoor,
  HomeHallwayLeftDoor,
  HomeLivingRoomRightDoor,
  HomeLivingRoomLeftDoor,
  None
};