#pragma once

#include "SummerIce/Util/CharacterEnum.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface: public UInterface
{
  GENERATED_BODY()

public:
  UInteractInterface(const class FObjectInitializer& ObjectInitializer);
};

class SUMMERICE_API IInteractInterface
{
  GENERATED_BODY()

public:
  virtual void ShowDialogWidget(const FString * Text = nullptr, const bool & bCanChooseLine = false) = 0;
  virtual void HideDialogWidget() = 0;

  virtual ECharacter GetName() const = 0;
  virtual int32 GetDialogId() const = 0;
};
