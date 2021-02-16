#pragma once
#include "GameEventType.generated.h"

UENUM(BlueprintType)
enum class EGameEventType: uint8
{
  TakeItem,
  RemoveItem,
  StartDialog,
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
  else if (Action.Equals("startdialog"))
    return EGameEventType::StartDialog;
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
  HomeHallway,
  HomeLivingRoom,
  HomeBathroom,
  HomeKitchen,
  None
};

UENUM(BlueprintType)
enum class EActionTiming: uint8
{
  OverlapBegin,
  OverlapEnd,
  PressInteractBtn,
  None
};