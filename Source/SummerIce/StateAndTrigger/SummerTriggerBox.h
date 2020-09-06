#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "StateAndTrigger/GameEventType.h"
#include "Util/GameItem.h"
#include "Util/CharacterEnum.h"
#include "SummerTriggerBox.generated.h"

UENUM(BlueprintType)
enum class EActionTiming: uint8
{
  OverlapBegin,
  OverlapEnd
};

UCLASS()
class SUMMERICE_API ASummerTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
  ASummerTriggerBox();
  
private:
  UFUNCTION()
  void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);

  UFUNCTION()
  void OnOverlapEnd(AActor * OverlappedActor, AActor * OtherActor);

  void ChooseEvent();

protected:
  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite)
  EGameEventType EventType = EGameEventType::NoAction;

  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite)
  EActionTiming EventTiming;

  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite,
            meta = (EditCondition = "EventType == EGameEventType::TakeItem || EventType == EGameEventType::RemoveItem"))
  EGameItem ItemType = EGameItem::None;
  
  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite,
            meta = (EditCondition = "EventType == EGameEventType::Teleport"))
  ETeleportLocation TeleportLocation = ETeleportLocation::None;

  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "false"))
  ECharacter CharacterType = ECharacter::Error;
};
